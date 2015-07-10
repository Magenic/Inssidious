/*
*  File:		main.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:	Creates and executes the QT application. 
*				Core work performed from inssidious.cpp.
*
*/

#include "inssidious.h"

bool runningAsAdmin();
bool runningOnWindows7OrNewer();

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QApplication::setEffectEnabled(Qt::UI_AnimateCombo, false); /* Resolves a drawing bug with Qt and extended frame windows */

	if (!runningAsAdmin())
	{
		MessageBox(NULL, L"Please run this application as an Administrator.", L"Inssidious requires Administrator rights.", MB_OK);
		return 1;
	}
	
	if (!runningOnWindows7OrNewer())
	{
		MessageBox(NULL, L"Inssidious can only run on Windows 7 or newer operating systems.", L"Inssidious requires Windows 7 or newer.", MB_OK);
		return 1;
	}

	Inssidious inssidious;
	inssidious.show();

	return a.exec();
}


//Function to confirm whether application is running with Administrator rights, required by Inssidious
bool runningAsAdmin()
{
	bool isRunningAsAdmin = false;									//Bool to store the result of our Administrator group check
	PSID pAdministratorsGroup = NULL;								//Pointer to memory to store the Administrator group SID in
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;	//SID of NtAuthority, needed to get the Administrator group SID 


	/* Allocate and initialize a SID of the administrators group. */
	
	if (AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pAdministratorsGroup))
	{

		/* Check our token's membership of the Administrator's group */

		if (CheckTokenMembership(NULL, pAdministratorsGroup, (PBOOL)&isRunningAsAdmin))
		{

			/* Free the memory we allocated and return the result as stored in isRunningAsAdmin */

			FreeSid(pAdministratorsGroup);
			return isRunningAsAdmin;
		}
	}


	/* If we land here, one of the calls failed. Return false */

	return false;
}


//Function to confirm whether application is running on Windows 7 or newer, required by Inssidious
bool runningOnWindows7OrNewer()
{
	OSVERSIONINFO osver = { sizeof(osver) };						//Struct to store the OS version info in when queried


	/* Get OS Version information */

	if (GetVersionEx(&osver))
	{

		/* If the OS Major Version is less than 6, it is older than Windows Vista and not supported */

		if (osver.dwMajorVersion < 6)
			return false;


		/* If the OS Major Version is 6 and the Minor Version is 0, then this is Windows Vista and not supported */

		if (osver.dwMajorVersion == 6 && osver.dwMinorVersion < 1)
			return false;

		/* All operating systems above version 6.0 are Windows 7 or newer and assumed supported */

		return true;
	}


	/* If we land here, the GetVersionEx call failed. Return false */
	
	return false;
}
