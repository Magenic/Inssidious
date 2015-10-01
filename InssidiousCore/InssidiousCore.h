#ifndef INSSIDIOUSCORE_H
#define INSSIDIOUSCORE_H

/*
*  File:		inssidiouscore.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "InterlockedPushListSList.h"
#pragma comment(lib, "..\\WinDivert\\x86\\WinDivert.lib")

#include <QThread>										//Core is a QThread running separately from the Inssidious UI

class HostedNetworkController;
class ICSController;
class DeviceController;
class DHCPController;
enum HostedNetworkReason;
enum TamperType;

class InssidiousCore : public QObject
{
	Q_OBJECT

public:
	InssidiousCore();


public slots:
	void onCoreInitialize();
	void onUiCoreStart(QString networkName, QString networkPassword, QString networkAdapter);									
	void onUiCoreStop();									
	void onUiTamperStart(QString MACAddress, int tamperType, void* pTamperConfig);
	void onUiTamperStop(QString MACAddress, int tamperType);


private:
	HostedNetworkController* hostedNetwork;
	ICSController* ics;
	DeviceController* deviceController;
	DHCPController* dhcpController;


private slots:
	void onCoreHostedNetworkMessage(QString message, HostedNetworkReason reason);								
	void onCoreDHCPipAddressAssigned(QString ipAddress, QString MACAddress);



signals:
	void coreVisibleNetworkConnections(QList<QString> visibleNetworkConnections);

	void coreStarting(QString statusMessage, bool error = false);
	void coreStarted();
	void coreStopped();

	void coreAddDevice(QString MACAddress);
	void coreDropDevice(QString MACAddress);
	void coreUpdateDevice(QString MACAddress, QString ipAddress);

	void coreTamperStart(QString MACAddress, TamperType tamperType, void* pTamperConfig);
	void coreTamperStop(QString MACAddress, TamperType tamperType);

};

#endif // INSSIDIOUSCORE_H
