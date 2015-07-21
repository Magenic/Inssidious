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

#include <QObject>							//Base class of HostedNetwork
#include <QUuid>							//For Qt helper functions handling GUIDs

#include <WinSock2.h>						//General Windows Networking types
#include <wtypes.h>							//Wireless Networking types
#include <Wlanapi.h>						//Wireless Networking API
#include <iphlpapi.h>						//General Networking Helper APIs
#include <comdef.h>							//Easy HRESULT error conversion

#pragma comment(lib, "wlanapi.lib")			//Wireless Networking API libary
#pragma comment(lib, "iphlpapi.lib")		//Networking Helper API library

#include "types.h"							//Shared types between Core components

class HostedNetwork : public QObject
{
	Q_OBJECT

public:
	HostedNetwork(QObject* parent);
	~HostedNetwork();

	//Performs legwork of configuring and starting the wireless hosted network
	bool initialize(QString networkName, QString networkPassword);


	//Callback that fires on HostedNetwork notifications from Windows, signals Core as appropriate
	static void __stdcall WlanNotificationCallback(PWLAN_NOTIFICATION_DATA, PVOID);


	//Used by Core to inform ICS who to set up the internet connection sharing against
	GUID hostedNetworkGUID;

signals:
	//Signal to notify Core of changes to the hosted network such as starting, stopping, and device arrivals
	void hostedNetworkMessage(QString message, HostedNetworkReason reason);


private:
	//Called on HostedNetwork instantiation, message boxes if hosted network is not enabled
	void isHostedNetworkCapable();


	//Restrict the number of devices connected to the hosted network to five for UI (space) and performance (untested)
	const DWORD maxNumberOfPeers = 5;
};

#endif // HOSTEDNETWORK_H
