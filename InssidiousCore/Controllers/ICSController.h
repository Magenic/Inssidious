/*
*  File:		ics.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/

#ifndef ICS_H
#define ICS_H


#include <QObject>							//Base of ICS class

#include <netcon.h>							//Required by CIcsManager for INet APIs
#include <atlstr.h>							//Required by CIcsManager for CAtlString
#include <atlcoll.h>						//Required by CIcsManager for CRefObjList & CAtlList
#include <IcsMgr/inc/common.h>				//Required by CIcsManager
#include <IcsMgr/inc/icsconn.h>				//Required by CIcsManager
#include <IcsMgr/inc/icsmgr.h>				//Provides CIcsManager

#include <comdef.h>							//Easy HRESULT error conversion


class ICSController : public QObject
{
	Q_OBJECT

public:
	ICSController();
	~ICSController();

	//Public list of network connection names used by UI and passed back in to identify connection to use
	QList<QString> networkConnectionNames;


	//Performs legwork of configuring and starting Internet Connection Sharing
	bool initialize(QString networkConnectionName, GUID hostedNetworkGUID);

	void stop();


	//Stores the error HRESULT on initialize failure
	HRESULT result;

private:
	//Checks if ICS has been disabled on this machine, message boxes if so
	bool isICSAllowed();


	//Instance of CIcsManager from the Microsoft sample project, defined in icsmgr.h
	CIcsManager* pICSManager;


	//List of available network connections populated via CIcsManager
	CRefObjList<CIcsConnectionInfo *> m_ConnectionList; 


	//Used to store the network connection name and GUID pair; only name used and passed back in by UI
	struct ICSNetworkConnections
	{
		QString networkConnectionName;
		GUID networkConnectionGUID;
	};
	QList<ICSNetworkConnections> icsNetworkConnectionList;

};

#endif // ICS_H
