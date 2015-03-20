#include "router.h"

bool Router::routerHasStarted = false;

Router::Router()
{

}

Router::~Router()
{

}

void __stdcall Router::WlanNotificationCallback(PWLAN_NOTIFICATION_DATA pNotifData, PVOID pContext)
{
	if (pNotifData == NULL || pNotifData->pData == NULL || pContext == NULL || WLAN_NOTIFICATION_SOURCE_HNWK != pNotifData->NotificationSource)
	{
		//Bad notification data or notification is from a source we don't want to watch
		return;
	}

	//pContext is a pointer to our router object for use emitting signals
	Router* router = (Router*)pContext;

	//Depending on the notification code type, respond differently
	if (pNotifData->NotificationCode == wlan_hosted_network_state_change)
	{
		//The notification data is of type PWLAN_HOSTED_NETWORK_STATE_CHANGE
		PWLAN_HOSTED_NETWORK_STATE_CHANGE pStateChange = (PWLAN_HOSTED_NETWORK_STATE_CHANGE)pNotifData->pData;

		//If the router has started, then a change in state to idle or unavailable is a critical failure
		if (routerHasStarted)
		{
			if (pStateChange->NewState == wlan_hosted_network_idle || pStateChange->NewState == wlan_hosted_network_unavailable)
			{
				emit router->routerFailed("The wireless hosted network has stopped unexpectedly.");
			}
		}
	}
	else if (pNotifData->NotificationCode == wlan_hosted_network_peer_state_change)
	{
		//The notification data is of type PWLAN_HOSTED_NETWORK_DATA_PEER_STATE_CHANGE
		PWLAN_HOSTED_NETWORK_DATA_PEER_STATE_CHANGE pPeerStateChange = (PWLAN_HOSTED_NETWORK_DATA_PEER_STATE_CHANGE)pNotifData->pData;

		//If a new device joined, emit deviceJoined with the MAC Address
		if (wlan_hosted_network_peer_state_authenticated == pPeerStateChange->NewState.PeerAuthState)
		{
			emit router->deviceConnected(QString(*pPeerStateChange->NewState.PeerMacAddress));
		}
		//If a device has left, emit deviceLeft with the MAC Address
		else if (wlan_hosted_network_peer_state_invalid == pPeerStateChange->NewState.PeerAuthState)
		{
			emit router->deviceDisconnected(QString(*pPeerStateChange->NewState.PeerMacAddress));
		}
	}
}



bool Router::start(QString networkName, QString networkPassword)
{
	DWORD negotiatedVersion = 0;					//DWORD for the Wlan API to store the negotiated API version in
	HRESULT result;									//HRESULT to store the return value from IP Helper API calls
	DWORD dwMaxNumberOfPeers = 8;					//Maximum number of clients that can connect, default is 100, 8 is required by hardware certification
	DOT11_SSID hostedNetworkSSID;					//DOT11_SSID struct to use later with WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS
	DWORD dwKeyLength;								//Length of the network password
	PUCHAR pucKeyData;								//Pointer to a UCHAR array for the network password text
	
	PWLAN_HOSTED_NETWORK_REASON pHostedNetworkFailReason = NULL;			// hosted network api call failure reason
	
	//Loop through and populate hostedNetworkSSID.ucSSID
	for (int i = 0; i < networkName.count(); i++)
	{
		hostedNetworkSSID.ucSSID[i] = networkName.at(i).unicode();
		hostedNetworkSSID.ucSSID[i + 1] = '\0'; //null the following character to ensure we have a null at the end of the loop
	}

	//Set the length of the array
	hostedNetworkSSID.uSSIDLength = networkName.count();

	//Initialize the WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS with the SSID and max peer count
	WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS hostedNetworkConnectionSettings{ hostedNetworkSSID, dwMaxNumberOfPeers };

	//Populate a UCHAR array with the network password
	dwKeyLength = networkPassword.count() + 1; //+1 as the API requests lenght include the null character
	pucKeyData = new UCHAR[networkPassword.count()+1]; //+1 as the API requests lenght include the null character
	for (int i = 0; i < networkPassword.count(); i++)
	{
		pucKeyData[i] = networkPassword.at(i).unicode();
		pucKeyData[i + 1] = '\0'; //null the following character to ensure we have a null at the end of the loop
	}



	//Open a handle to the Wlan API for after GetAdapterAddresses
	result = WlanOpenHandle(
		WLAN_API_VERSION_2_0,						//Request API version 2.0
		NULL,										//Reserved
		&negotiatedVersion,							//Address of the DWORD to store the negotiated version
		&wlanHandle									//Address of the HANDLE to store the Wlan handle
		);

	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		emit routerFailed("Unable to open a handle to the Wlan API. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//Register for hosted network notifications
	result = WlanRegisterNotification(
		wlanHandle,									//Wlan handle
		WLAN_NOTIFICATION_SOURCE_HNWK,				//Specifically receive Hosted Network notifications
		TRUE,										//Don't send duplicate notifications
		&WlanNotificationCallback,					//WLAN_NOTIFICATION_CALLBACK function to call with notifactions
		this,										//Context to pass along with the notification
		NULL,										//Reserved
		NULL										//Previously registered notification sources
		);

	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		emit routerFailed("Unable to register for Wlan Hosted Network Notifications. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//Stop any existing running Hosted Network
	result = WlanHostedNetworkForceStop(
		wlanHandle,									//Wlan handle
		pHostedNetworkFailReason,					//Pointer to where the API can store a failure reason in
		NULL										//Reserved
		);

	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		emit routerFailed("Unable to stop an existing, running Hosted Network. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//Initialize the hosted network as a precursor to setting specific settings
	result = WlanHostedNetworkInitSettings(
		wlanHandle,									//Wlan handle
		pHostedNetworkFailReason,					//Pointer to where the API can store a failure reason in
		NULL										//Reserved
		);

	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		emit routerFailed("Unable to initialize hosted network settings. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//Set the Hosted Network network name and peer count
	result = WlanHostedNetworkSetProperty(
		wlanHandle,										//Wlan handle
		wlan_hosted_network_opcode_connection_settings, //Type of data being passed to the API
		sizeof(hostedNetworkConnectionSettings),		//Size of the data at the pointer to hosted network connection settings
		(PVOID)&hostedNetworkConnectionSettings,		//Pointer to the hosted network connection settings we are setting
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		NULL											//Reserved
		);

	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		emit routerFailed("Unable to set hosted network settings. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//Set the Hosted Network password 
	result = WlanHostedNetworkSetSecondaryKey(
		wlanHandle,										//Wlan handle
		dwKeyLength,									//Length of the network password array including the null character
		pucKeyData,										//Pointer to a UCHAR array with the network password
		TRUE,											//Is a pass phrase
		TRUE,											//Do not persist this key for future hosted network sessions
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		NULL											//Reserved
		);

	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		emit routerFailed("Unable to set hosted network password. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//Start hosted network
	result = WlanHostedNetworkStartUsing(
		wlanHandle,										//Wlan handle
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		NULL											//Reserved
		);

	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		emit routerFailed("Unable to start the wireless hosted network. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//Check hosted network status
	PWLAN_HOSTED_NETWORK_STATUS pHostedNetworkStatus = NULL;
	result = WlanHostedNetworkQueryStatus(
		wlanHandle,										//Wlan handle
		&pHostedNetworkStatus,							//Pointer to a pointer for HOSTED_NETWORK_STATUS
		NULL											//Reserved
		);
	
	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		emit routerFailed("Unable to query hosted network status. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}
	
	//Store the GUID of the virtual wireless device broadcasting the hosted network
	virtualWirelessDeviceGUID = pHostedNetworkStatus->IPDeviceID;

	//Free the memory allocated for pHostedNetworkStatus
	if (pHostedNetworkStatus != NULL)
	{
		WlanFreeMemory(pHostedNetworkStatus);
		pHostedNetworkStatus = NULL;
	}

	//We now want to pay attention to notifications indicating the hosted network stopped
	routerHasStarted = true;

	return true;
}
