#include "core.h"

QList<NetworkAdapter> Core::NetworkAdapterList;

Core::Core()
{
	//No heavy lifting is done here
	//InssidiousUi moves Core to it's own thread and Core catches Qt's signal when the new thread starts
}

Core::~Core()
{

}

void Core::onThreadStarted()
{
	//Check if the app is running with Admin rights
	if (!runningAsAdmin())
	{
		//We are not running as an Administrator. Notify InssidiousUI and return
		emit coreFailed("Inssidious must be run as Administrator.");
		return;
	}
	
	//Check if the app is running on Windows 7 or a newer OS
	if (!runningOnWindows7OrNewer())
	{
		//We are not running on Windows 7 or newer. Notify InssidiousUI and return
		emit coreFailed("Inssidious can only run on Windows 7 or newer. Sorry :(");
		return;
	}

	//Build the list of network adapters, minimum one wireless adapter
	if (!getNetworkAdapters())
	{
		//A blocking error occured and InssidiousUI was signaled from within getNetworkAdapters()
		return;
	}

	//All pre-start checks have passed, signal that Core is ready to start
	emit coreReadyToStart();

	/* No further action taken until StartupWidget emits coreStartInssidiou */
}

void Core::onCoreStartInssidious(QString networkName, QString networkPassword)
{
	
	Router* router = new Router();
	connect(router, &Router::routerFailed, this, &Core::onRouterFailed);					//Connect router failures to Core's onRouterFailed for cleanup & signal ferrying
	connect(router, &Router::deviceConnected, this, &Core::coreDeviceConnected);
	connect(router, &Router::deviceDisconnected, this, &Core::coreDeviceDisconnected);

	if (!router->start(networkName, networkPassword))
	{
		//Router failed to start and emitted a signal that Core passed on to InssidiousUi
		return;
	}

	if (true)
	{
		emit coreStarted(networkName, networkPassword);
	}
	else
	{
		
	}
}

void Core::onRouterFailed(QString errorMessage)
{
	//Clean up

	//Emit the signal to InssidiousUi
	emit coreFailed(errorMessage);
}

//void Core::onRouterDeviceConnected(DOT11_MAC_ADDRESS MACAddress)
//{
//	emit coreDeviceConnected(MACAddress);
//}
//void Core::onRouterDeviceDisconnected(DOT11_MAC_ADDRESS MACAddress)
//{
//	emit coreDeviceDisconnected(MACAddress);
//}

bool Core::runningAsAdmin()
{
	bool isRunningAsAdmin = false;		//Will pass to CheckTokenMembership
	PSID pAdministratorsGroup = NULL;	//Will store the SID to check the token against

	//Allocate and initialize a SID of the administrators group.
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pAdministratorsGroup))
	{
		//If we successfully did so, check the token membership
		if (CheckTokenMembership(NULL, pAdministratorsGroup, (PBOOL)&isRunningAsAdmin))
		{
			//If we successfully did so, free the memory we allocated and return the value stored in isRunningAsAdmin
			FreeSid(pAdministratorsGroup);
			return isRunningAsAdmin;
		}
	}

	//Something went wrong. Free allocated memory and return false
	if (pAdministratorsGroup)
	{
		FreeSid(pAdministratorsGroup);
	}
	return false;
}

bool Core::runningOnWindows7OrNewer()
{
	OSVERSIONINFO osver = { sizeof(osver) }; // MUST initialize with the size or GetVersionEx fails
	if (GetVersionEx(&osver)) 
	{
		if (osver.dwMajorVersion < 6)
		{
			//Less than 6 is an operating system older than Windows Vista, not supported
			return false;
		}

		if (osver.dwMajorVersion == 6 && osver.dwMinorVersion < 1)
		{
			//6.0 is Vista and also not supported
			return false;
		}

		//We're 6.1 or above, operating system should be supported
		return true;
	}

	//GetVersionEx call failed
	return false;
}

bool Core::getNetworkAdapters()
{
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
		//Clear the list, emit an error, and return.
		NetworkAdapterList.clear();
		emit coreFailed("Unable to open a handle to the Wlan API. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//GetAdaptersAddresses requires an allocated buffer. Loop calling it until we have allocated enough memory
	do 
	{
		pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(ulOutBufLen);

		if (pAddresses == NULL) //Should never be null after malloc
		{
			//Clear the list, emit an error, and return.
			NetworkAdapterList.clear();
			emit coreFailed("Unable to allocate memory needed to call GetAdapterInfo.\nPlease restart Inssidious and try again.");
			return false;
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
		//Clear the list, emit an error, and return.
		NetworkAdapterList.clear();
		emit coreFailed("No network adapters found. Please enable or connect network\nadapters to the system and restart Inssidious.");
		return false;
	}
	else if (result != NO_ERROR) //Some other error occurred
	{
		//Clear the list, append an error, and return.
		NetworkAdapterList.clear();
		emit coreFailed("Unable to get network adapter information. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}


	//PIP_ADAPTER_ADDRESSES is a linked list, we'll need to traverse the entries
	PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; 
	while (pCurrAddresses)
	{
		//Only add Ethernet and Wireless adapters to the list
		if ((pCurrAddresses->IfType == IF_TYPE_ETHERNET_CSMACD)) //ethernet
		{
			NetworkAdapter net{ pCurrAddresses->AdapterName, QString::fromWCharArray(pCurrAddresses->Description), ETHERNET };
			NetworkAdapterList.prepend(net);
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
				NetworkAdapterList.prepend(net);
			}
			else //does not support hosted networks
			{
				NetworkAdapter net{ pCurrAddresses->AdapterName, QString::fromWCharArray(pCurrAddresses->Description), WIRELESS };
				NetworkAdapterList.prepend(net);
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
		//Clear the list, emit an error, and return.
		NetworkAdapterList.clear();
		emit coreFailed("No wireless network adapter found. Please enable or connect a\n wireless adapter and restart Inssidious.");
		return false;
	}

	//Close the wlanHandle
	WlanCloseHandle(wlanHandle, NULL);

	//Free the memory we allocated and return the list
	FREE(pAddresses);
	return true;
}
