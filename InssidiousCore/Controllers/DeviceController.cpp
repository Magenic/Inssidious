#include "DeviceController.h"

DeviceController::DeviceController()
{

	connect(this, &DeviceController::dcUpdateDevice, this, &DeviceController::onCoreUpdateDevice, Qt::DirectConnection);
}

DeviceController::~DeviceController()
{

}

void DeviceController::onCoreAddDevice(QString MACAddress)
{

	/* Create a tcDevice */

	deviceList.append(new device());
	deviceList.last()->MACAddress = MACAddress;
	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		deviceList.last()->enabled[i] = false;
	}
	deviceList.last()->divertController = new DivertController(deviceList.last());


	/* Check if we already have an IP for device, possible race */

	for (LostPair* lp : lostPairs)
	{
		if (lp->MACAddress == deviceList.last()->MACAddress)
		{
			emit dcUpdateDevice(deviceList.last()->MACAddress, lp->ipAddress);

			lostPairs.removeOne(lp);
		}
	}


	connect(this, &DeviceController::dcDivertStop, deviceList.last()->divertController, &DivertController::onDivertStop);
	connect(deviceList.last()->divertController, &DivertController::divertStopped, this, &DeviceController::onDivertStopped);

	/* No further work until we get an IP address */
}


void DeviceController::onCoreDropDevice(QString MACAddress)
{

	/* Search through the tab list for the matching MAC address */

	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress)
		{
			/* Stop the Divert threads */

			emit dcDivertStop();

			break;
		}
	}
}


void DeviceController::onCoreUpdateDevice(QString MACAddress, QString ipAddress)
{

	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress && d->IPAddress != ipAddress)
		{
			d->IPAddress = ipAddress;
			
			if (!d->started)
			{
				d->divertController->start();
				d->started = true;
			}
			else
			{
				d->updateIPAddress = true;
				emit dcDivertStop();
			}
			return;
		}
	}

	
	/* No matching device, store the MAC & IP for now */

	lostPairs.append(new LostPair{ MACAddress, ipAddress });
	
}


void DeviceController::onCoreTamperStart(QString MACAddress, TamperType tamperType)
{
	/* Search through the tab list for the matching MAC address */

	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress)
		{
			d->enabled[tamperType] = true;
		}
	}
}

void DeviceController::onCoreTamperStop(QString MACAddress, TamperType tamperType)
{
	/* Search through the tab list for the matching MAC address */

	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress)
		{
			d->enabled[tamperType] = false;
		}
	}
}

void DeviceController::onDivertStopped(QString MACAddress)
{
	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress)
		{
			if (d->updateIPAddress)
			{
				d->divertController->createThreads();
			}
			else
			{
				deviceList.removeOne(d);
				delete d;
			}
		}
	}
}