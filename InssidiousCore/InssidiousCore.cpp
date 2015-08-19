/*
*  File:		inssidiouscore.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "InssidiousCore.h"
#include "Controllers\HostedNetworkController.h"		//Hosted network class to start and manage the wireless network
#include "Controllers\ICSController.h"					//Internet Connection Sharing class to start and manage ICS
#include "Controllers\TamperController.h"				//Tamper Controller class to manage tamper instances

InssidiousCore::InssidiousCore()
{

	/* Initialize instances of the Hosted Network, ICS, and TamperController classes */
	/* Error conditions such as no wireless card will trigger a Messagebox & quit the app */

	hostedNetwork = new HostedNetworkController(this);
	ics = new ICSController(this);
	tamperController = new TamperController();


	/* Grab a pointer to the list of network connection names for use by Inssidious */

	pNetworkConnectionNames = &ics->networkConnectionNames;


	/* Connect Signals and Slots */
	
	connect(this, &InssidiousCore::coreTamperStart, tamperController, &TamperController::onCoreTamperStart);
	connect(this, &InssidiousCore::coreTamperStop, tamperController, &TamperController::onCoreTamperStop);
	connect(tamperController, &TamperController::coreTamperStarted, this, &InssidiousCore::onCoreTamperStarted);
	connect(tamperController, &TamperController::coreTamperStopped, this, &InssidiousCore::onCoreTamperStopped);


	connect(this, &InssidiousCore::coreAddDevice, tamperController, &TamperController::onCoreAddDevice);
	connect(this, &InssidiousCore::coreDropDevice, tamperController, &TamperController::onCoreDropDevice);


	connect(hostedNetwork, &HostedNetworkController::hostedNetworkMessage, this, &InssidiousCore::onCoreHostedNetworkMessage, Qt::DirectConnection);

	/* No further work until we receive signals */

}

InssidiousCore::~InssidiousCore()
{

}


//Calls QThread exec() to start the thread's event loop
void InssidiousCore::run()
{
	QThread::exec();
}


//Receives a notification from the Startup Widget with info to start the hosted network and ICS with
void InssidiousCore::onUiCoreStart(QString networkName, QString networkPassword, QString networkConnection)
{

	/* Configure Hosted Network Settings and confirm Hosted Network is allowed on machine */
	/* Initialize the hosted network first, as that may change the available ICS connections */

	if (!hostedNetwork->initialize(networkName, networkPassword))
	{
		/* Something went wrong, we'll have displayed the message. Stop initialization */

		return;
	}


	/* Start Internet Connection Sharing */

	emit coreStarting("Starting Internet Connection Sharing.", false);
	if (!ics->initialize(networkConnection, hostedNetwork->hostedNetworkGUID))
	{
		/* Something went wrong, display a message and stop initialization. */

		emit coreStarting("Unable to start Internet Connection Sharing. Error:\n"
			+ QString::fromWCharArray(_com_error(ics->result).ErrorMessage()), true);
		return;
	}


	/* Success! */

	emit coreStarting("Started Internet Connection Sharing.", false);
	emit coreStarted();

}

void InssidiousCore::onUiCoreStartTamper(QString MACAddress, QString TamperType)
{
	emit coreTamperStart(MACAddress, TamperType);
}

void InssidiousCore::onUiCoreStopTamper(QString MACAddress, QString TamperType)
{
	emit coreTamperStop(MACAddress, TamperType);
}

void InssidiousCore::onCoreTamperStarted(QString MACAddress, QString TamperType)
{
	emit coreTamperStarted(MACAddress, TamperType);
}

void InssidiousCore::onCoreTamperStopped(QString MACAddress, QString TamperType)
{
	emit coreTamperStopped(MACAddress, TamperType);
}


//Receives notifications from the Hosted Network class with status and error info
void InssidiousCore::onCoreHostedNetworkMessage(QString message, HostedNetworkReason reason)
{
	switch (reason)
	{
	case HOSTED_NETWORK_STARTING:
		emit coreStarting(message, false /* not an error */);
		break;
	case HOSTED_NETWORK_STARTING_FAILED:
		emit coreStarting(message, true /* an error occured */);
		break;
	case HOSTED_NETWORK_STARTED:
		emit coreStarting(message, false /* not an error */);
		break;
	case HOSTED_NETWORK_STOPPED:
		/* The Hosted Network stopped unexpectedly */
		/* TODO: cleanup and critical error */
		break;
	case DEVICE_CONNECTED:
		emit coreAddDevice(message /* device MAC address */);
		/*TODO: have a list of tamper controllers and add a new instance to it */
		break;
	case DEVICE_DISCONNECTED:
		emit coreDropDevice(message /* device MAC address */);
		/*TODO: remove the appropriate tamper controller from the list */
		break;
	}
}

