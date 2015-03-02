#include "core.h"

Core::Core()
{
	//initialize some pointers from core.h
	//no heavy lifting here
}

Core::~Core()
{

}

void Core::onThreadStart()
{
	//Do actual initialization work

	if (true)
	{
		emit coreStarted();
	}
	else
	{
		emit coreStartFailed("Error message");
	}
}

void Core::onInssidiousStart()
{

	if (true)
	{
		emit inssidiousStarted();
	}
	else
	{
		emit inssidiousStartFailed("Error message");
	}
}


bool Core::getWirelessInterfaces(QList<QString>* foundWirelessInterfaces)
{
	HANDLE wlanHandle;								//Wlan API Handle
	PWLAN_INTERFACE_INFO_LIST wlanInterfaces;		//List of Wlan Interfaces returned by API
	HRESULT result = 0;								//HRESULT to store the return value from Wlan API calls
	DWORD negotiatedVersion = 0;					//DWORD for the Wlan API to store the negotiated API version in


	//Open a handle to the Wlan API
	result = WlanOpenHandle(
		WLAN_API_VERSION_2_0,						//Request API version 2.0
		NULL,										//Reserved
		&negotiatedVersion,							//Address of the DWORD to store the negotiated version
		&wlanHandle									//Address of the HANDLE to store the Wlan handle
		);

	//If the result isn't NO_ERROR, something went wrong. 
	if (result != NO_ERROR)
	{
		//Clear the foundWirelessInterfaces list, append the error, and return false.
		foundWirelessInterfaces->clear();
		foundWirelessInterfaces->append("Unable to open handle to the Wlan API. Error:\n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//Enumerate the wireless network interfaces
	result = WlanEnumInterfaces(
		wlanHandle,									//The HANDLE returned by WlanOpenHandle
		NULL,										//Reserved
		&wlanInterfaces								//Address of the pointer to store the location to the interface data in
		);

	//If the result isn't NO_ERROR, something went wrong.
	if (result != NO_ERROR)
	{
		//Clear the foundWirelessInterfaces list, append the error, and return false.
		foundWirelessInterfaces->clear();
		foundWirelessInterfaces->append("Unable to enumerate wireless interfaces. Error:\n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()));
		return false;
	}

	//If wlanInterfaces has no items, there are no wireless adapters on the system.
	if (wlanInterfaces->dwNumberOfItems == 0)
	{
		//Clear the foundWirelessInterfaces list, append the error, and return false.
		foundWirelessInterfaces->clear();
		foundWirelessInterfaces->append("No wireless adapters found. Please enable or connect a wireless\nadapter to the system and restart Inssidious.");
		return false;
	}

	//Otherwise, append each interface name to the list
	foundWirelessInterfaces->clear();
	for (int i = 0; i < wlanInterfaces->dwNumberOfItems; i++)
	{
		foundWirelessInterfaces->append(QString::fromWCharArray(wlanInterfaces->InterfaceInfo[i].strInterfaceDescription));
	}

	
	return true;
}

bool Core::getAllNetworkInterfaces(QList<QString>* foundNetworkInterfaces)
{
	// Declare and initialize variables
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
	ULONG ulOutBufLen = 0;
	int maxBufferTries = 20;
	DWORD dwRetVal = 0;

	// Make an initial call to GetInterfaceInfo to get the necessary size in the ulOutBufLen variable
	dwRetVal = GetInterfaceInfo(NULL, &ulOutBufLen);

	do {
		pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(ulOutBufLen);

		if (pAddresses == NULL)
		{
			//Clear the foundNetworkInterfaces list, append the error, and return false.
			foundNetworkInterfaces->clear();
			foundNetworkInterfaces->append("Unable to allocate memory needed to call GetInterfaceInfo.");
			return false;
		}

		// Make a call to GetInterfaceInfo to get the data we need
		dwRetVal = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, pAddresses, &ulOutBufLen);

		if (dwRetVal == ERROR_BUFFER_OVERFLOW) 
		{
			FREE(pAddresses);
			pAddresses = NULL;
		}
		else 
		{
			break;
		}

		maxBufferTries--;

	} while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (maxBufferTries > 0));


	//If the error is ERROR_NO_DATA, there are no network adapters on the system.
	if (dwRetVal == ERROR_NO_DATA) 
	{
		//Clear the foundNetworkInterfaces list, append the error, and return false.
		foundNetworkInterfaces->clear();
		foundNetworkInterfaces->append("No network adapters found. Please enable or connect network\nadapters to the system and restart Inssidious.");
		return false;
	}
	else if (dwRetVal != NO_ERROR) //Some other error occurred
	{
		//Clear the foundNetworkInterfaces list, append the error, and return false.
		foundNetworkInterfaces->clear();
		foundNetworkInterfaces->append("Unable to get network adapter information. Error: \n   " + QString::fromWCharArray(_com_error(dwRetVal).ErrorMessage()));
		return false;
	}

	//Otherwise, append each interface name to the list
	foundNetworkInterfaces->clear();
	PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses;
	while (pCurrAddresses)
	{
		foundNetworkInterfaces->append(QString::fromWCharArray(pCurrAddresses->Description));
		pCurrAddresses = pCurrAddresses->Next;
	}


	FREE(pAddresses);
	return true;
}
