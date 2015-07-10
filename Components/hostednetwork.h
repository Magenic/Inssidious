/*
*  File:		hostednetwork.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/

#ifndef HOSTEDNETWORK_H
#define HOSTEDNETWORK_H

#include <QObject>
#include <QUuid>							//For Qt helper functions handling GUIDs

#include <WinSock2.h>						//General Windows Networking types
#include <wtypes.h>							//Wireless Networking types
#include <Wlanapi.h>						//Wireless Networking API
#include <iphlpapi.h>						//General Networking Helper APIs
#include <comdef.h>							//Easy HRESULT error conversion

#pragma comment(lib, "wlanapi.lib")			//Wireless Networking API libary
#pragma comment(lib, "iphlpapi.lib")		//Networking Helper API library

#include "types.h"							//

class HostedNetwork : public QObject
{
	Q_OBJECT

public:
	HostedNetwork(QObject* parent);
	~HostedNetwork();

	bool initialize(QString networkName, QString networkPassword);

	static void __stdcall WlanNotificationCallback(PWLAN_NOTIFICATION_DATA, PVOID);

	GUID hostedNetworkGUID;

signals:
	void hostedNetworkMessage(QString message, HostedNetworkReason reason);

private:
	const DWORD maxNumberOfPeers = 8;

	void isHostedNetworkCapable();

};

#endif // HOSTEDNETWORK_H
