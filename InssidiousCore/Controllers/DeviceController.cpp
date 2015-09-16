#include "DeviceController.h"

#include <InssidiousCore/Controllers/DivertController.h>


DeviceController::DeviceController()
{

}


void DeviceController::onCoreAddDevice(QString MACAddress)
{

	/* Create a tcDevice */

	deviceList.append(new device());
	device* d = deviceList.last();
	
	d->MACAddress = MACAddress;
	d->IPAddress = "";

	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		d->tamperModuleConfig[i] = nullptr;
		d->tamperModuleActive[i] = false;
	}

	d->divertController = new DivertController(d->MACAddress, d->tamperModuleConfig, d->tamperModuleActive);
	d->divertController->start();

	/* Connect the updateIPAddress, stop, and stopped signals and slots */

	connect(this, &DeviceController::divertUpdateIPAddress, d->divertController, &DivertController::onDivertUpdateIPAddress);
	connect(this, &DeviceController::divertStop, d->divertController, &DivertController::onDivertStop);
	connect(d->divertController, &DivertController::divertStopped, this, &DeviceController::onDivertStopped);



	/* Check if we already have an IP for device. Order-of-Operations-wise, 
		we should always get the add device signal from the hosted network 
		controller before getting an IP address from the DHCP controller, 
		but this a potential race condition with the Qt signals so let's 
		protect against it. */


	for (MAC_IP_Pair* lostPair : lostPairs)
	{
		if (lostPair->MACAddress == d->MACAddress)
		{
			/* We had a lost MAC/IP pair. Set the info and remove the lost pair */

			d->IPAddress = lostPair->ipAddress;
			lostPairs.removeOne(lostPair);


			/* Signal to divert to update its IP Address */

			emit divertUpdateIPAddress(d->MACAddress, d->IPAddress);

			break;
		}
	}	
}


void DeviceController::onCoreDropDevice(QString MACAddress)
{

	/* Search through the tab list for the matching MAC address */

	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress)
		{
			/* Remove the device from the deviceList and pend its deletion */
			
			deviceList.removeOne(d);
			pendingDeletionList.append(d);


			/* Stop the divert threads. Remaining deletion work signaled from there */

			emit divertStop(MACAddress);
			return;
		}
	}
}


void DeviceController::onCoreUpdateDevice(QString MACAddress, QString ipAddress)
{

	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress)
		{
			if (d->IPAddress == ipAddress)
			{
				/* We already have the right IP Address */

				return;
			}
			else
			{
				/* Update the IP address */

				d->IPAddress = ipAddress;
				emit divertUpdateIPAddress(MACAddress, ipAddress);

				return;
			}
		}
	}

	
	/* We don't have this device in the deviceList yet. */


	/* Check if the MACAddress is in the lost pair list, and if so, update the IP Address */

	for (MAC_IP_Pair* lostPair : lostPairs)
	{
		if (lostPair->MACAddress == MACAddress)
		{
			lostPair->ipAddress = ipAddress;
			return;
		}
	}


	/* This MAC is new to us, store it as a lost MAC/IP pair */

	lostPairs.append(new MAC_IP_Pair{ MACAddress, ipAddress });
	
}


void DeviceController::onCoreTamperStart(QString MACAddress, TamperType tamperType, void* pTamperConfig)
{
	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress)
		{
			d->tamperModuleConfig[tamperType] = pTamperConfig;
			d->tamperModuleActive[tamperType] = true;

			return;
		}
	}
}

void DeviceController::onCoreTamperStop(QString MACAddress, TamperType tamperType)
{
	for (device * d : deviceList)
	{
		if (d->MACAddress == MACAddress)
		{
			d->tamperModuleActive[tamperType] = false;

			return;
		}
	}
}

void DeviceController::onDivertStopped(QString MACAddress)
{
	/* All packets processed, safe to delete device */

	for (device * d : pendingDeletionList)
	{
		if (d->MACAddress == MACAddress)
		{
			pendingDeletionList.removeOne(d);
			delete d->divertController;
			delete d;

			return;
		}
	}
}