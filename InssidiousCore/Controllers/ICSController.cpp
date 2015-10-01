/*
*  File:		ics.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "ICSController.h"

ICSController::ICSController()
{
	/* Check if ICS is disabled */

	if (!isICSAllowed())
	{
		MessageBox(nullptr, 
			L"ICS has been disabled on this computer.",
			L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);
	}

	/* Prepare for COM */

	::CoInitializeEx(nullptr, COINIT_MULTITHREADED);


	/* Get an instance of the IcsMgr and initialize it */

	pICSManager = new CIcsManager();
	HRESULT result = pICSManager->InitIcsManager();
	if (result != S_OK)
	{
		/* Something went wrong */

		MessageBox(nullptr, reinterpret_cast<const wchar_t*>(QString(
			           ("Unable to prepare Internet Connection Sharing. Error: \n   ")
			           + QString::fromWCharArray(_com_error(result).ErrorMessage())
		           ).utf16()),
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
				QString::fromWCharArray(static_cast<LPCWSTR>(connection->m_Name)));
			icsNetworkConnectionList.append({
				QString::fromWCharArray(static_cast<LPCWSTR>(connection->m_Name)),
				connection->m_Guid});
		}
	}

}

ICSController::~ICSController()
{
	 
	delete pICSManager;
	pICSManager = nullptr;

	::CoUninitialize();
	NSModDeinit();
}

void ICSController::stop()
{
	/* The list of available connections can change after the hosted network starts. Reset the ICS Manager */

	pICSManager->ResetIcsManager();


	/* Disable all existing ICS configurations */

	pICSManager->DisableIcsOnAll();

}

//Performs legwork of configuring and starting Internet Connection Sharing
bool ICSController::initialize(QString networkConnectionName, GUID hostedNetworkGUID)
{
	/* The list of available connections can change after the hosted network starts. Reset the ICS Manager */

	pICSManager->ResetIcsManager();


	/* Disable all existing ICS configurations */
	
	pICSManager->DisableIcsOnAll();


	/* And Reset the ICS Manager Again */

	pICSManager->ResetIcsManager();


	/* Start ICS between the network connection the user selected and the hosted network */

	for (ICSNetworkConnections networkConnection : icsNetworkConnectionList)
	{
		if (networkConnection.networkConnectionName == networkConnectionName)
		{ 
			/* Found the connection in icsNetworkConnectionList, now have the GUID */

			/* Try starting ICS a few times.. */

			int loop30 = 0;
			while (loop30 < 30)
			{
				loop30++;
				result = pICSManager->EnableIcs(networkConnection.networkConnectionGUID, hostedNetworkGUID);
				if (result != S_OK)
				{
					Sleep(500);
					continue;
				}
				else
				{
					break;
				}
			}

			if (result != S_OK)
			{
				/* We can't start ICS */
					
				return false;
			}
			else
			{
				/* ICS started successfully */

				return true;
			}
		}
	}
	

	/* We should never end up here */

	result = ERROR_UNEXP_NET_ERR;
	return false;
}


//Check a Registry value to confirm ICS has not been disabled on this machine
bool ICSController::isICSAllowed()
{
	/* Open the Registry key that contains the value we need to check */
	
	HKEY  hAllowICSRegKey = nullptr;		//Handle to the registry key that contains the value we need to check
	DWORD result = ERROR_SUCCESS;			//Result DWORD to check for API call errors

	result = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		L"SOFTWARE\\Policies\\Microsoft\\Windows\\Network Connections",
		0,
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
		nullptr,
		L"NC_ShowSharedAccessUI",
		RRF_RT_DWORD,
		nullptr,
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