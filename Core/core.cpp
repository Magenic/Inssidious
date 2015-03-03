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
	HRESULT result;									//HRESULT to store the return value from IP Helper API calls
	bool atLeastOneWirelessAdapter = false;			//Inssidious requires at least one wireless adapter to be present
	
	//GetAdaptersAddresses requires an allocated buffer. Loop calling it until we have allocated enough memory
	do 
	{
		pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(ulOutBufLen);

		if (pAddresses == NULL) //Should never be null after malloc
		{
			//Clear the list, append an error, and return.
			NetworkAdapter err{ "Error", "Unable to allocate memory needed to call GetAdapterInfo.\nPlease restart Inssidious and try again.", ERRORMESSAGE };
			lNetworkAdapters.clear();
			lNetworkAdapters.append(err);
			return lNetworkAdapters;
		}

		//Call GetAdaptersAddresses to get network adapter info
		result = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, pAddresses, &ulOutBufLen);

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
		NetworkAdapter err{ "Error", "No network adapters found. Please enable or connect network\nadapters to the system and restart Inssidious.", ERRORMESSAGE };
		lNetworkAdapters.clear();
		lNetworkAdapters.append(err);
		return lNetworkAdapters;
	}
	else if (result != NO_ERROR) //Some other error occurred
	{
		//Clear the list, append an error, and return.
		NetworkAdapter err{ "Error", "Unable to get network adapter information. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), ERRORMESSAGE };
		lNetworkAdapters.clear();
		lNetworkAdapters.append(err);
		return lNetworkAdapters;
	}


	//PIP_ADAPTER_ADDRESSES is a linked list, we'll need to traverse the entries
	PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; 
	while (pCurrAddresses)
	{
		//Only add Ethernet and Wireless adapters to the list
		if ((pCurrAddresses->IfType == IF_TYPE_ETHERNET_CSMACD))
		{
			NetworkAdapter net{ pCurrAddresses->AdapterName, QString::fromWCharArray(pCurrAddresses->Description), ETHERNET };
			lNetworkAdapters.prepend(net);
		}
		else if ((pCurrAddresses->IfType == IF_TYPE_IEEE80211))
		{
			NetworkAdapter net{ pCurrAddresses->AdapterName, QString::fromWCharArray(pCurrAddresses->Description), WIRELESS };
			lNetworkAdapters.prepend(net);

			atLeastOneWirelessAdapter = true; //we have at least one wireless adapter
		}
		
		//Move through the linked list
		pCurrAddresses = pCurrAddresses->Next;
	}

	if (!atLeastOneWirelessAdapter) //We do not have a wireless adapter in the list.
	{
		//Clear the list, append an error, and return.
		NetworkAdapter err{ "Error", "No wireless network adapter found. Please enable or connect a\n wireless adapter and restart Inssidious.", ERRORMESSAGE };
		lNetworkAdapters.clear();
		lNetworkAdapters.append(err);
		return lNetworkAdapters;
	}

	//Free the memory we allocated and return the list
	FREE(pAddresses);
	return lNetworkAdapters;
}
