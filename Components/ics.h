#ifndef ICS_H
#define ICS_H

#include <QObject>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <netcon.h>
#include <new>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS    // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>
#include <atlcoll.h>
#include <strsafe.h>
#include <comdef.h>							//Easy HRESULT error conversion

#include "IcsMgr\common.h"
#include "IcsMgr\icsconn.h"
#include "IcsMgr\icsmgr.h"



#pragma comment(lib, "Components\\IcsMgr\\IcsMgr.lib")		//IcsMgr library


class ICS : public QObject
{
	Q_OBJECT

public:
	ICS(QObject *parent);
	~ICS();

	QList<QString> networkConnectionNames;


	//
	bool initialize(QString networkConnectionName, GUID hostedNetworkGUID);


private:
	
	CIcsManager* pICSManager;				//Pointer to an instance of the ICS Manager from icsmgr.h

	CRefObjList<CIcsConnectionInfo *> m_ConnectionList; // List of connections (adapters)

	struct ICSNetworkConnections
	{
		QString networkConnectionName;
		GUID networkConnectionGUID;
	};
	QList<ICSNetworkConnections> icsNetworkConnectionList;

	
	//Check a Registry value to confirm ICS has not been disabled on this machine
	bool isICSAllowed();


};

#endif // ICS_H
