#include "DeviceController.h"

DeviceController::DeviceController()
{
	
}

DeviceController::~DeviceController()
{

}

void DeviceController::onCoreAddDevice(QString MACAddress)
{

	/* Create a tcDevice */

	deviceList.append(new DivertController(MACAddress));


	/* Start the DivertController thread */

	deviceList.last()->start();


}


void DeviceController::onCoreDropDevice(QString MACAddress)
{

	/* Search through the tab list for the matching MAC address */

	for (DivertController* d : deviceList)
	{
		if (d->MAC == MACAddress)
		{
			/* Delete from the list */

			deviceList.removeOne(d);
			//d->stop();
			delete d;
			break;
		}
	}
}


void DeviceController::onCoreTamperStart(QString MACAddress, TamperType tamperType)
{
	/* Search through the tab list for the matching MAC address */

	for (DivertController* d : deviceList)
	{
		if (d->MAC == MACAddress)
		{
			d->enabled[tamperType] = true;
		}
	}
}

void DeviceController::onCoreTamperStop(QString MACAddress, TamperType tamperType)
{
	/* Search through the tab list for the matching MAC address */

	for (DivertController* d : deviceList)
	{
		if (d->MAC == MACAddress)
		{
			d->enabled[tamperType] = false;
		}
	}
}