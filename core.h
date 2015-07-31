/*
*  File:		core.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/

#ifndef CORE_H
#define CORE_H

#include <QThread>							//Core is a QThread running separately from the Inssidious UI

#include "Components\hostednetwork.h"		//Hosted network class to start and manage the wireless network
#include "Components\ics.h"					//Internet Connection Sharing class to start and manage ICS


class Core : public QThread
{
	Q_OBJECT

public:
	Core();
	~Core();

	QList<QString>* pNetworkConnectionNames;						//Public list of network connection names to share with Startup widget
	void run();														//Calls QThread exec() to start the thread's event loop


public slots:
	void onCoreStart(QString networkName,							//Receives a notification from the Startup Widget with the network name,
						QString networkPassword,					//Password,
						QString networkAdapter);					//And adapter to start the wireless hosted network and ICS with
	void onHostedNetworkMessage(QString message,					//Receives notifications from the Hosted Network class with status and error info
					HostedNetworkReason reason);					//Function conditions on the reason code defined in types.h


signals:
	void updateStatus(QString statusMessage, bool error = false);	//Core signals status information as the backend starts up
	void started();													//Core signals when completely started
	void deviceConnected(QString);									//Core signals with the MAC address when a new device has connected
	void deviceDisconnected(QString);								//Core signals with the MAC address when a new device has disconnected

private:

	HostedNetwork* hostedNetwork;									//Instance of the hosted network class
	ICS* ics;														//Instance of the internet connection sharing class

};

#endif // CORE_H
