#include "ics.h"

ICS::ICS(QObject *parent)
	: QObject(parent)
{
	/* Check if ICS is disabled */

	if (!isICSAllowed())
	{
		MessageBox(NULL, 
			L"ICS has been disabled on this computer.",
			L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);
	}

	/* Prepare for COM */

	::CoInitializeEx(NULL, COINIT_MULTITHREADED);


	/* Get an instance of the IcsMgr and initialize it */

	pICSManager = new CIcsManager();
	HRESULT result = pICSManager->InitIcsManager();
	if (result != S_OK)
	{
		/* Something went wrong */

		MessageBox(NULL, (const wchar_t*)QString(
			("Unable to prepare Internet Connection Sharing. Error: \n   ")
			+ QString::fromWCharArray(_com_error(result).ErrorMessage())
			).utf16(),
			L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);
	}


	/* Populate a list of available network connections */

	pICSManager->GetIcsConnections(m_ConnectionList);
	for (size_t i = 0; i < m_ConnectionList.GetCount(); i++)
	{
		CIcsConnectionInfo* connection = m_ConnectionList.GetAt(m_ConnectionList.FindIndex(i));
		
		/* If the connection supports Internet Connection Sharing, get the ID and Name */

		if (connection->m_Supported)
		{
			networkConnectionNames.append(
				QString::fromWCharArray((LPCWSTR)connection->m_Name));
			icsNetworkConnectionList.append({
				QString::fromWCharArray((LPCWSTR)connection->m_Name),
				connection->m_Guid});
		}
	}

}

ICS::~ICS()
{
	/* 
	delete pICSManager;
	pICSManager = NULL;

	::CoUninitialize();
	NSModDeinit();
	
	*/
}


bool ICS::initialize(QString networkConnectionName, GUID hostedNetworkGUID)
{
	/* Disable all existing ICS Settings */
	pICSManager->DisableIcsOnAll();


	/* Start ICS between the network connection the user selected and the hosted network */

	for (ICSNetworkConnections networkConnection : icsNetworkConnectionList)
	{
		if (networkConnection.networkConnectionName == networkConnectionName)
		{ 
			/* Found the connection in icsNetworkConnectionList, now have the GUID */

			if (S_OK == pICSManager->EnableIcs(networkConnection.networkConnectionGUID, hostedNetworkGUID))
			{
				return true;
			}
		}
	}

	return false;
}


//Check a Registry value to confirm ICS has not been disabled on this machine
bool ICS::isICSAllowed()
{
	/* Open the Registry key that contains the value we need to check */
	
	HKEY  hAllowICSRegKey = NULL;		//Handle to the registry key that contains the value we need to check
	DWORD result = ERROR_SUCCESS;		//Result DWORD to check for API call errors

	result = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		L"SOFTWARE\\Policies\\Microsoft\\Windows\\Network Connections",
		NULL,
		KEY_READ,
		&hAllowICSRegKey
		);
	if (result != ERROR_SUCCESS || !hAllowICSRegKey)
	{
		/* Something went wrong */

		return false;
	}


	/* Query for the specific ICS value */

	DWORD   ValLen = sizeof(DWORD);
	DWORD   dwAllowIcs = 1;

	result = RegGetValue(
		hAllowICSRegKey,
		NULL,
		L"NC_ShowSharedAccessUI",
		RRF_RT_DWORD,
		NULL,
		&dwAllowIcs,
		&ValLen
		);
	if (result == ERROR_SUCCESS && dwAllowIcs == 0)
	{
		/* ICS is disabled on this machine. */

		return false;;
	}


	/* ICS is enabled. Close the registry key and return true. */

	RegCloseKey(hAllowICSRegKey);

	return true;
}