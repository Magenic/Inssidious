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

	/* Populate QLists with the system's network adapters */
	/* Some error conditions such as no wireless card will Messagebox & quit the app */


	hostedNetwork = new HostedNetwork(this);
	ics = new ICS(this);

	pNetworkConnectionNames = &ics->networkConnectionNames;

}

Core::~Core()
{

	/* Clear all settings and stop Hosted Network and ICS */
}

void Core::run()
{
	QThread::exec();
}

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
		emit updateStatus("Unable to start Internet Connection Sharing. Error: \n" + GetLastError(), true);

		return;
	}

	
	/* Success! */
	emit updateStatus("Started Internet Connection Sharing.", false);
	emit started();

}


//
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
		break;
	case DEVICE_DISCONNECTED:
		emit deviceDisconnected(message /* device MAC address */);
		break;
	}
}

