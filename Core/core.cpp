#include "core.h"

Core::Core()
{
	//initialize some pointers from core.h
	//no heavy lifting here
}

Core::~Core()
{

}

void Core::onThreadStarted()
{
	//Do actual initialization work

	if (true)
	{
		emit coreThreadReady();
	}
	else
	{
		emit inssidiousCriticalError("Error message");
	}
}

void Core::onCoreStartInssidious()
{

	if (true)
	{
		emit inssidiousStarted();
		emit deviceConnected();
		emit deviceConnected();
		emit deviceConnected();
	}
	else
	{
		emit inssidiousCriticalError("Error message");
	}
}

QList<Core::NetworkAdapter> Core::getNetworkAdapters()
{
	QList<Core::NetworkAdapter> lNetworkAdapters;	//List of NetworkAdapter structs to return
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;		//Pointer to store information from GetAdaptersAddresses in
	ULONG ulOutBufLen = 0;							//Buffer for PIP_ADAPTER_ADDRESSES information
	int maxBufferBumps = 20;						//Number of times to try increasing buffer to accomodate data
	HANDLE wlanHandle;								//Handle to call WlanQueryInterface to check interface capabilities
	DWORD negotiatedVersion = 0;					//DWORD for the Wlan API to store the negotiated API version in
	HRESULT result;									//HRESULT to store the return value from IP Helper API calls
	bool atLeastOneWirelessAdapter = false;			//Inssidious requires at least one wireless adapter to be present
	

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
		//Clear the list, append an error, and return.
		NetworkAdapter err{ "Error", "Unable to open a handle to the Wlan API. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), ERROR_QUERYING_ADAPTERS };
		lNetworkAdapters.clear();
		lNetworkAdapters.append(err);
		return lNetworkAdapters;
	}

	//GetAdaptersAddresses requires an allocated buffer. Loop calling it until we have allocated enough memory
	do 
	{
		pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(ulOutBufLen);

		if (pAddresses == NULL) //Should never be null after malloc
		{
			//Clear the list, append an error, and return.
			NetworkAdapter err{ "Error", "Unable to allocate memory needed to call GetAdapterInfo.\nPlease restart Inssidious and try again.", ERROR_QUERYING_ADAPTERS };
			lNetworkAdapters.clear();
			lNetworkAdapters.append(err);
			return lNetworkAdapters;
		}
		
		//Call GetAdaptersAddresses to get network adapter info
		result = GetAdaptersAddresses(AF_INET, 0, NULL, pAddresses, &ulOutBufLen);

		if (result != ERROR_BUFFER_OVERFLOW) //GetAdapterAddresses returned something. Break out of the loop
		{
			break;
		}
		else //We need moar buffer, the looping continues
		{
			FREE(pAddresses);
			pAddresses = NULL;
			maxBufferBumps--;
		}
	} while (maxBufferBumps > 0); //As a fallback, stop after 20 buffer bumps


	//If the error is ERROR_NO_DATA, there are no network adapters on the system.
	if (result == ERROR_NO_DATA)
	{
		//Clear the list, append an error, and return.
		NetworkAdapter err{ "Error", "No network adapters found. Please enable or connect network\nadapters to the system and restart Inssidious.", ERROR_QUERYING_ADAPTERS };
		lNetworkAdapters.clear();
		lNetworkAdapters.append(err);
		return lNetworkAdapters;
	}
	else if (result != NO_ERROR) //Some other error occurred
	{
		//Clear the list, append an error, and return.
		NetworkAdapter err{ "Error", "Unable to get network adapter information. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), ERROR_QUERYING_ADAPTERS };
		lNetworkAdapters.clear();
		lNetworkAdapters.append(err);
		return lNetworkAdapters;
	}


	//PIP_ADAPTER_ADDRESSES is a linked list, we'll need to traverse the entries
	PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; 
	while (pCurrAddresses)
	{
		//Only add Ethernet and Wireless adapters to the list
		if ((pCurrAddresses->IfType == IF_TYPE_ETHERNET_CSMACD)) //ethernet
		{
			NetworkAdapter net{ pCurrAddresses->AdapterName, QString::fromWCharArray(pCurrAddresses->Description), ETHERNET };
			lNetworkAdapters.prepend(net);
		}
		else if ((pCurrAddresses->IfType == IF_TYPE_IEEE80211)) //wireless
		{
			//We have at least one wireless adapter!
			atLeastOneWirelessAdapter = true; 

			//We need to additionally confirm hosted network capability for the wireless adapters

			//Create a QUuid from the char* in pCurrAddresses
			QUuid qtAdapterGuid(pCurrAddresses->AdapterName);

			//Cast it to a Windows GUID
			GUID windowsAdapterGuid = static_cast<GUID>(qtAdapterGuid);

			//Create two variables for WlanQueryInterface to store the query response in
			DWORD responseSize = NULL;
			PBOOL pHostedNetworkCapable = NULL;

			//Query whether the wireless adapter supports Hosted Networks
			result = WlanQueryInterface(wlanHandle, &windowsAdapterGuid, wlan_intf_opcode_hosted_network_capable, NULL, &responseSize, (PVOID *)&pHostedNetworkCapable, NULL);

			//If pHostedNetworkCapable contains any value other than zero, the adapter supports Hosted Networks
			if (result == S_OK && *pHostedNetworkCapable) //supports hosted networks
			{
				NetworkAdapter net{ pCurrAddresses->AdapterName, QString::fromWCharArray(pCurrAddresses->Description), WIRELESS_HOSTED_NETWORK_CAPABLE };
				lNetworkAdapters.prepend(net);
			}
			else //does not support hosted networks
			{
				NetworkAdapter net{ pCurrAddresses->AdapterName, QString::fromWCharArray(pCurrAddresses->Description), WIRELESS };
				lNetworkAdapters.prepend(net);
			}

			//Free the memory Wlan allocated for us
			if (pHostedNetworkCapable != NULL)
			{
				WlanFreeMemory(pHostedNetworkCapable);
				pHostedNetworkCapable = NULL;
			}
		}
		
		//Move through the linked list
		pCurrAddresses = pCurrAddresses->Next;
	}

	if (!atLeastOneWirelessAdapter) //We do not have a wireless adapter in the list.
	{
		//Clear the list, append an error, and return.
		NetworkAdapter err{ "Error", "No wireless network adapter found. Please enable or connect a\n wireless adapter and restart Inssidious.", ERROR_QUERYING_ADAPTERS };
		lNetworkAdapters.clear();
		lNetworkAdapters.append(err);
		return lNetworkAdapters;
	}

	//Close the wlanHandle
	WlanCloseHandle(wlanHandle, NULL);

	//Free the memory we allocated and return the list
	FREE(pAddresses);
	return lNetworkAdapters;
}
