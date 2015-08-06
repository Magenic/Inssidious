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


#include <QThread>										//Core is a QThread running separately from the Inssidious UI

#include "Controllers\HostedNetworkController.h"		//Hosted network class to start and manage the wireless network
#include "Controllers\ICSController.h"					//Internet Connection Sharing class to start and manage ICS
#include "Controllers\TamperController.h"				//Tamper Controller class to manage tamper instances

class InssidiousCore : public QThread
{
	Q_OBJECT

public:
	InssidiousCore();
	~InssidiousCore();

	QList<QString>* pNetworkConnectionNames;						//Public list of network connection names to share with Startup widget
	void run();														//Calls QThread exec() to start the thread's event loop

signals:
	void coreStarting(QString statusMessage, bool error = false);
	void coreStarted();													
	void coreStopped();													

	void coreAddDevice(QString MACAddress);
	void coreDropDevice(QString MACAddress);	

	void coreTamperStart(QString MACAddress, QString TamperType);
	void coreTamperStop(QString MACAddress, QString TamperType);

	void coreTamperStarted(QString MACAddress, QString TamperType);
	void coreTamperStopped(QString MACAddress, QString TamperType);


public slots:
	void onUiCoreStart(QString networkName, QString networkPassword, QString networkAdapter);									
	void onUiCoreStartTamper(QString MACAddress, QString TamperType);
	void onUiCoreStopTamper(QString MACAddress, QString TamperType);


	void onCoreTamperStarted(QString MACAddress, QString TamperType);
	void onCoreTamperStopped(QString MACAddress, QString TamperType);

	void onCoreHostedNetworkMessage(QString message, HostedNetworkReason reason);								




private:

	HostedNetworkController* hostedNetwork;	
	ICSController* ics;	
	TamperController* tamperController;
};

#endif // INSSIDIOUSCORE_H
