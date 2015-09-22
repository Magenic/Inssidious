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
#include "Controllers\DeviceController.h"				//Tamper Controller class to manage tamper instances
#include "Controllers\DHCPController.h"

InssidiousCore::InssidiousCore()
{

	/* Initialize instances of the Hosted Network, ICS, and DeviceController classes */
	/* Error conditions such as no wireless card will trigger a Messagebox & quit the app */

	hostedNetwork = new HostedNetworkController(this);
	ics = new ICSController(this);
	deviceController = new DeviceController();
	dhcpController = new DHCPController();

	/* Grab a pointer to the list of network connection names for use by Inssidious */

	pNetworkConnectionNames = &ics->networkConnectionNames;


	/* Connect Signals and Slots */

	connect(dhcpController, &DHCPController::ipAddressAssigned, this, &InssidiousCore::onCoreDHCPipAddressAssigned);

	connect(this, &InssidiousCore::coreAddDevice, deviceController, &DeviceController::onCoreAddDevice);
	connect(this, &InssidiousCore::coreDropDevice, deviceController, &DeviceController::onCoreDropDevice);
	connect(this, &InssidiousCore::coreUpdateDevice, deviceController, &DeviceController::onCoreUpdateDevice);

	connect(this, &InssidiousCore::coreTamperStart, deviceController, &DeviceController::onCoreTamperStart);
	connect(this, &InssidiousCore::coreTamperStop, deviceController, &DeviceController::onCoreTamperStop);

	connect(hostedNetwork, &HostedNetworkController::hostedNetworkMessage, this, &InssidiousCore::onCoreHostedNetworkMessage, Qt::DirectConnection);


	/* No further work until we receive signals */

}




//Calls QThread exec() to start the thread's event loop
void InssidiousCore::run()
{
	QThread::exec();
}


//Receives a notification from the Startup Widget with info to start the hosted network and ICS with
void InssidiousCore::onUiCoreStart(QString networkName, QString networkPassword, QString networkConnection)
{

	/* Start the Divert DHCP thread */

	dhcpController->start();


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

		MessageBox(nullptr, reinterpret_cast<const wchar_t*>(QString(
			("Unable to start Internet Connection Sharing. Error:\n")
			+ QString::fromWCharArray(_com_error(ics->result).ErrorMessage())
			).utf16()),
			L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);

		return;
	}

	emit coreStarting("Started Internet Connection Sharing.", false);


	/* Success! */

	emit coreStarted();

}

void InssidiousCore::onUiCoreStop()
{
	hostedNetwork->stop();
}


void InssidiousCore::onUiTamperStart(QString MACAddress, int tamperType, void* pTamperConfig)
{
	emit coreTamperStart(MACAddress, TamperType(tamperType), pTamperConfig);
}

void InssidiousCore::onUiTamperStop(QString MACAddress, int tamperType)
{
	emit coreTamperStop(MACAddress, TamperType(tamperType));
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
		MessageBox(nullptr, L"The Hosted Network failed to start.", L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);
		break;
	case HOSTED_NETWORK_STARTED:
		emit coreStarting(message, false /* not an error */);
		break;
	case HOSTED_NETWORK_STOPPED:
		/* The Hosted Network stopped unexpectedly */
		/* TODO: cleanup and critical error */

		MessageBox(nullptr, L"The Hosted Network stopped unexpectedly.", L"Inssidious was forced to stop.", MB_OK);
		ExitProcess(1);

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

void InssidiousCore::onCoreDHCPipAddressAssigned(QString MACAddress, QString ipAddress)
{
	emit coreUpdateDevice(MACAddress, ipAddress);
}