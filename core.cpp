/*
*  File:		core.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "core.h"


Core::Core()
{

	/* Initialize instances of the Hosted Network and ICS classses */
	/* Error conditions such as no wireless card will trigger a Messagebox & quit the app */

	hostedNetwork = new HostedNetwork(this);
	ics = new ICS(this);


	/* Grab a pointer to the list of network connection names for use by Inssidious */

	pNetworkConnectionNames = &ics->networkConnectionNames;


	/* Initialize the Tamper Controller and connect some signals */
	tamperController = new TamperController();
	connect(this, &Core::deviceConnected, tamperController, &TamperController::onDeviceConnected);
	connect(this, &Core::deviceDisconnected, tamperController, &TamperController::onDeviceDisconnected);

	/* No further work until the Startup widget signals */
}

Core::~Core()
{

}


//Calls QThread exec() to start the thread's event loop
void Core::run()
{
	QThread::exec();
}


//Receives a notification from the Startup Widget with info to start the hosted network and ICS with
void Core::onCoreStart(QString networkName, QString networkPassword, QString networkConnection)
{

	/* Configure Hosted Network Settings and confirm Hosted Network is allowed on machine */
	
	connect(hostedNetwork, &HostedNetwork::hostedNetworkMessage,
		this, &Core::onHostedNetworkMessage, Qt::DirectConnection);


	/* Initialize the hosted network first, as that may change the available ICS connections */

	if (!hostedNetwork->initialize(networkName, networkPassword))
	{
		/* Something went wrong, we'll have displayed the message. Stop initialization */

		return;
	}


	/* Start Internet Connection Sharing */

	emit updateStatus("Starting Internet Connection Sharing.", false);
	if (!ics->initialize(networkConnection, hostedNetwork->hostedNetworkGUID))
	{
		/* Something went wrong, display a message and stop initialization. */

		emit updateStatus("Unable to start Internet Connection Sharing. Error:\n" 
			+ QString::fromWCharArray(_com_error(ics->result).ErrorMessage()), true);
		return;
	}

	
	/* Success! */

	emit updateStatus("Started Internet Connection Sharing.", false);
	emit started();

}


//Receives notifications from the Hosted Network class with status and error info
void Core::onHostedNetworkMessage(QString message, HostedNetworkReason reason)
{
	switch (reason)
	{
	case HOSTED_NETWORK_STARTING:
		emit updateStatus(message, false /* not an error */);
		break;
	case HOSTED_NETWORK_STARTING_FAILED:
		emit updateStatus(message, true /* an error occured */);
		break;
	case HOSTED_NETWORK_STARTED:
		emit updateStatus(message, false /* not an error */);
		break;
	case HOSTED_NETWORK_STOPPED:
		/* The Hosted Network stopped unexpectedly */
		/* TODO: cleanup and critical error */
		break;
	case DEVICE_CONNECTED:
		emit deviceConnected(message /* device MAC address */);
		/*TODO: have a list of tamper controllers and add a new instance to it */
		break;
	case DEVICE_DISCONNECTED:
		emit deviceDisconnected(message /* device MAC address */);
		/*TODO: remove the appropriate tamper controller from the list */
		break;
	}
}

