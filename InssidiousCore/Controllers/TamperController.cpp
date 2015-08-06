#include "TamperController.h"

TamperController::TamperController()
{

}

TamperController::~TamperController()
{

}

void TamperController::onCoreAddDevice(QString MACAddress)
{
	tcDeviceList.append(new tcDevice);
	tcDeviceList.last()->MAC = MACAddress;

}


void TamperController::onCoreDropDevice(QString MACAddress)
{

	/* Search through the tab list for the matching MAC address */

	for (tcDevice* d : tcDeviceList)
	{
		if (d->MAC == MACAddress)
		{
			/* Delete from the list */

			tcDeviceList.removeOne(d);
			break;
		}
	}
}


void TamperController::onCoreTamperStart(QString MACAddress, QString TamperType)
{

}

void TamperController::onCoreTamperStop(QString MACAddress, QString TamperType)
{

}