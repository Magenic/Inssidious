/*
*  File:		hostednetwork.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/

#include "HostedNetworkController.h"


HostedNetworkController::HostedNetworkController(QObject *parent)
	: QObject(parent)
{

	isHostedNetworkCapable();

}

HostedNetworkController::~HostedNetworkController()
{

}


//Performs legwork of configuring and starting the wireless hosted network
bool HostedNetworkController::initialize(QString networkName, QString networkPassword)
{

	/* Create variables to receive the result of Wlan API calls */

	HRESULT result;													//HRESULT to store the return value 
	PWLAN_HOSTED_NETWORK_REASON pHostedNetworkFailReason = NULL;	//Pointer to the specific call failure reason
	DWORD negotiatedVersion = 0;									//DWORD for the Wlan API to store the negotiated API version in
	HANDLE wlanHandle;												//Handle to call WlanQueryInterface to check interface capabilities

	/* Open a handle to the Wlan API */
	result = WlanOpenHandle(
		WLAN_API_VERSION_2_0,						//Request API version 2.0
		NULL,										//Reserved
		&negotiatedVersion,							//Address of the DWORD to store the negotiated version
		&wlanHandle									//Address of the HANDLE to store the Wlan handle
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to open a handle to the Wlan API. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Stop any existing running Hosted Network */
	
	emit hostedNetworkMessage("Stopping any currently running Hosted Networks.", HOSTED_NETWORK_STARTING);
	result = WlanHostedNetworkForceStop(
		wlanHandle,									//Wlan handle
		pHostedNetworkFailReason,					//Pointer to where the API can store a failure reason in
		NULL										//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to stop an existing, running Hosted Network. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Initialize the hosted network as a precursor to setting specific settings */
	
	emit hostedNetworkMessage("Preparing to initialize settings.", HOSTED_NETWORK_STARTING);
	result = WlanHostedNetworkInitSettings(
		wlanHandle,									//Wlan handle
		pHostedNetworkFailReason,					//Pointer to where the API can store a failure reason in
		NULL										//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to initialize hosted network settings. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Prepare the network name in the appropriate SSID format */

	DOT11_SSID hostedNetworkSSID;						//DOT11_SSID struct to use later with WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS
	hostedNetworkSSID.uSSIDLength = networkName.count();//Set the length of the array in th uSSIDLength struct value
	for (int i = 0; i < networkName.count(); i++)		//Fill the ucSSID array
	{
		hostedNetworkSSID.ucSSID[i] = networkName.at(i).unicode();
		hostedNetworkSSID.ucSSID[i + 1] = '\0';			//Null the next character to ensure we have a null at the end of the loop
	}
	

	/* Initialize the WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS with the SSID and max peer count */
	/* And Set the Hosted Network network name and peer count */

	emit hostedNetworkMessage("Setting the network name and password.", HOSTED_NETWORK_STARTING);
	WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS hostedNetworkConnectionSettings{ hostedNetworkSSID, maxNumberOfPeers };
	result = WlanHostedNetworkSetProperty(
		wlanHandle,										//Wlan handle
		wlan_hosted_network_opcode_connection_settings, //Type of data being passed to the API
		sizeof(hostedNetworkConnectionSettings),		//Size of the data at the pointer to hosted network connection settings
		(PVOID)&hostedNetworkConnectionSettings,		//Pointer to the hosted network connection settings we are setting
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		NULL											//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to set hosted network settings. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Prepare the network password in the appropriate UCHAR format */

	DWORD dwKeyLength = networkPassword.count() + 1;	//Length of the network password, needed for the API call, +1 for the null
	PUCHAR pucKeyData = new UCHAR[dwKeyLength];			//Initialize our UCHAR variable
	for (int i = 0; i < networkPassword.count(); i++)	//Fill the array
	{
		pucKeyData[i] = networkPassword.at(i).unicode();
		pucKeyData[i + 1] = '\0';						//Null the next character to ensure we have a null at the end of the loop
	}


	/* Set the Hosted Network password */

	result = WlanHostedNetworkSetSecondaryKey(
		wlanHandle,										//Wlan handle
		dwKeyLength,									//Length of the network password array including the null character
		pucKeyData,										//Pointer to a UCHAR array with the network password
		TRUE,											//Is a pass phrase
		TRUE,											//Do not persist this key for future hosted network sessions
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		NULL											//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to set hosted network password. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Start the Hosted Network */

	emit hostedNetworkMessage("Starting the Hosted Network.", HOSTED_NETWORK_STARTING);
	result = WlanHostedNetworkStartUsing(
		wlanHandle,										//Wlan handle
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		NULL											//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to start the wireless hosted network. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Register to receive hosted network related notifications in our callback function */

	result = WlanRegisterNotification(
		wlanHandle,									//Wlan handle
		WLAN_NOTIFICATION_SOURCE_HNWK,				//Specifically receive Hosted Network notifications
		TRUE,										//Don't send duplicate notifications
		&WlanNotificationCallback,					//WLAN_NOTIFICATION_CALLBACK function to call with notifactions
		this,										//Context to pass along with the notification
		NULL,										//Reserved
		NULL										//Previously registered notification sources
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to register for Wlan Hosted Network Notifications. Error: \n" + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Check the hosted network status */

	PWLAN_HOSTED_NETWORK_STATUS pHostedNetworkStatus = NULL;
	result = WlanHostedNetworkQueryStatus(
		wlanHandle,										//Wlan handle
		&pHostedNetworkStatus,							//Pointer to a pointer for HOSTED_NETWORK_STATUS
		NULL											//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to query hosted network status. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* The Hosted Network started. Free memory, emit the status, save the network GUID, and return true */

	hostedNetworkGUID = pHostedNetworkStatus->IPDeviceID;

	if (pHostedNetworkStatus != NULL)
	{
		WlanFreeMemory(pHostedNetworkStatus);
		pHostedNetworkStatus = NULL;
	}

	emit hostedNetworkMessage("Hosted Network started successfully.", HOSTED_NETWORK_STARTED);

	return true;
}


//Callback that fires on HostedNetwork notifications from Windows, signals Core as appropriate
void __stdcall HostedNetworkController::WlanNotificationCallback(PWLAN_NOTIFICATION_DATA pNotifData, PVOID pContext)
{

	/* If the notification data is empty or from a source other than Hosted Networks, we don't want to touch it */

	if (pNotifData == NULL || pNotifData->pData == NULL || pContext == NULL || WLAN_NOTIFICATION_SOURCE_HNWK != pNotifData->NotificationSource)
	{
		return;
	}


	/* pContext is a pointer to our HostedNetwork class instance we can use to emit signals */ 
	HostedNetworkController* hostedNetwork = (HostedNetworkController*)pContext;


	/* React to Network State or Network Peer changes */

	if (pNotifData->NotificationCode == wlan_hosted_network_state_change)
	{
		/* A change in state to idle or unavailable is a critical failure */
		
		PWLAN_HOSTED_NETWORK_STATE_CHANGE pStateChange = (PWLAN_HOSTED_NETWORK_STATE_CHANGE)pNotifData->pData;
		if (pStateChange->NewState == wlan_hosted_network_idle || pStateChange->NewState == wlan_hosted_network_unavailable)
		{
			emit hostedNetwork->hostedNetworkMessage("The wireless hosted network has stopped unexpectedly.", HOSTED_NETWORK_STOPPED);
		}
	}
	else if (pNotifData->NotificationCode == wlan_hosted_network_peer_state_change)
	{
		/* A device has joined or left the network */

		PWLAN_HOSTED_NETWORK_DATA_PEER_STATE_CHANGE pPeerStateChange = (PWLAN_HOSTED_NETWORK_DATA_PEER_STATE_CHANGE)pNotifData->pData;
		if (wlan_hosted_network_peer_state_authenticated == pPeerStateChange->NewState.PeerAuthState)
		{
			emit hostedNetwork->hostedNetworkMessage(QString(*pPeerStateChange->NewState.PeerMacAddress), DEVICE_CONNECTED);
		}
		else if (wlan_hosted_network_peer_state_invalid == pPeerStateChange->NewState.PeerAuthState)
		{
			emit hostedNetwork->hostedNetworkMessage(QString(*pPeerStateChange->NewState.PeerMacAddress), DEVICE_DISCONNECTED);
		}
	}
}


//Called on HostedNetwork instantiation, message boxes if hosted network is not enabled
void HostedNetworkController::isHostedNetworkCapable()
{
	HANDLE wlanHandle;								//Handle to use with Wlan API calls
	HRESULT result;									//HRESULT to store the return value from IP Helper API calls
	bool atLeastOneHostedNetworkSupport = false;	//Inssidious requires at least one wireless adapter with hosted network support


	/* Open a handle to the Wlan API */

	DWORD negotiatedVersion = 0;					//DWORD for the Wlan API to store the negotiated API version in
	result = WlanOpenHandle(
		WLAN_API_VERSION_2_0,						//Request API version 2.0
		NULL,										//Reserved
		&negotiatedVersion,							//Address of the DWORD to store the negotiated version
		&wlanHandle									//Address of the HANDLE to store the Wlan handle
		);

	if (result != NO_ERROR)
	{
		/* Something went wrong */

		MessageBox(NULL, (const wchar_t*)QString(
			("Unable to open a handle to the Wlan API. Error: \n   ")
			+ QString::fromWCharArray(_com_error(result).ErrorMessage())
			).utf16(),
			L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);
	}


	/* Get a list of all network adapters on the system */

	PIP_ADAPTER_ADDRESSES pAddresses = NULL;		//Pointer to store information from GetAdaptersAddresses in
	ULONG ulOutBufLen = 0;							//Buffer for PIP_ADAPTER_ADDRESSES information
	int remainingRetries = 20;						//Number of times to try increasing buffer to accomodate data
	while (remainingRetries > 0)						//Loop to repeatedly try to populate PIP_ADAPTER_ADDRESSES buffer
	{
		remainingRetries--;


		/* Allocate memory */

		pAddresses = (IP_ADAPTER_ADDRESSES *)HeapAlloc(GetProcessHeap(), 0, (ulOutBufLen));

		if (pAddresses == NULL)
		{
			/* Something went wrong */

			MessageBox(NULL, L"Unable to allocate memory needed to call GetAdapterInfo.\
							  				\nPlease restart Inssidious and try again.",
											L"Inssidious failed to start.", MB_OK);
			ExitProcess(1);
		}


		/* Try to get network adapter information */

		result = GetAdaptersAddresses(AF_INET, 0, NULL, pAddresses, &ulOutBufLen);

		if (result == ERROR_BUFFER_OVERFLOW)
		{
			/* We need more memory. ulOutBufLen now has the size needed */
			/* Free what we allocated, null pAddresses, and continue. */

			HeapFree(GetProcessHeap(), 0, (pAddresses));
			pAddresses = NULL;
			continue;
		}
		else if (result == ERROR_NO_DATA)
		{
			/* The system has no network adapters. */

			MessageBox(NULL, L"No network adapters found. Please enable or connect network\
							  				\nadapters to the system and restart Inssidious.",
											L"Inssidious failed to start.", MB_OK);
			ExitProcess(1);
		}
		else if (result != NO_ERROR || remainingRetries == 0)
		{
			/* Something went wrong */

			MessageBox(NULL, (const wchar_t*)QString(
				("Unable to get network adapter information. Error: \n   ")
				+ QString::fromWCharArray(_com_error(result).ErrorMessage())
				).utf16(),
				L"Inssidious failed to start.", MB_OK);
			ExitProcess(1);
		}
		else
		{
			/* We successfully retreived the network adapter list. Leave the loop */

			break;
		}
	}


	/* Traverse the list of network adapters to identify hosted network capable wireless adapters */

	PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses;					//Pointer to travse entries in the linked list
	while (pCurrAddresses)
	{
		if ((pCurrAddresses->IfType == IF_TYPE_IEEE80211))
		{

			/* Check whether the adapter supports running a wireless hosted network */
			/* Support for this is required by all wireless cards certified for Windows 7 or newer */

			DWORD responseSize = NULL;									//DWORD for the Wlan API to store the size of its reply in
			PBOOL pHostedNetworkCapable = NULL;							//Pointer to a bool for hosted network capabilities
			result = WlanQueryInterface(
				wlanHandle,												//Handle to the WLAN API opened earlier
				&(GUID(QUuid(pCurrAddresses->AdapterName))),			//Char Array to Qt Uuid to GUID of the adapter ID
				wlan_intf_opcode_hosted_network_capable,				//Asking specifically on hosted network support
				NULL,													//Reserved
				&responseSize,											//Size of the response received
				(PVOID *)&pHostedNetworkCapable,						//Bool for whether adapter supports hosted network
				NULL													//Optional return data type value
				);

			if (result == S_OK && *pHostedNetworkCapable)
			{
				/* This adapter supports wireless hosted networks. */
				/* Flag that we met the requirement of at least one wireless adapter on the system supporting hosted networks */

				atLeastOneHostedNetworkSupport = true;
			}


			/* Free the memory the Wlan API allocated for us */

			if (pHostedNetworkCapable != NULL)
			{
				WlanFreeMemory(pHostedNetworkCapable);
				pHostedNetworkCapable = NULL;
			}
		}

		/* Continue moving through the the linked list of adapters */

		pCurrAddresses = pCurrAddresses->Next;
	}


	/* All adapters have been processed. Free the memory allocated for the adapter list. */

	HeapFree(GetProcessHeap(), 0, (pAddresses));


	/* Check if any adapters supported Wireless Hosted Networks. */
	/* Inssidious requires at least one wireless adapter with Hosted Network support */

	if (!atLeastOneHostedNetworkSupport)
	{
		MessageBox(NULL, L"No wireless network adapters with Hosted Network Support were\
						  			\n found. Please insert or enable another wireless adapter and restart Inssidious.",
									L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);
	}
	else
	{
		return;
	}
}