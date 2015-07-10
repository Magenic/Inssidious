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

#include <QThread>

#include "Components\types.h"				//
#include "Components\hostednetwork.h"		//
#include "Components\ics.h"					//


class Core : public QThread
{
	Q_OBJECT

public:
	Core();
	~Core();

	QList<QString>* pNetworkConnectionNames;
	void run();

public slots:
	void onCoreStart(QString networkName,
						QString networkPassword,
						QString networkAdapter);
	void onHostedNetworkMessage(QString message, 
					HostedNetworkReason reason);


signals:
	void updateStatus(QString statusMessage, bool error = false);
	void started();

private:

	/* */

	HostedNetwork* hostedNetwork;
	ICS* ics;


};

#endif // CORE_H
