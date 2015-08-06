#include "TamperController.h"

TamperController::TamperController()
{

}

TamperController::~TamperController()
{

}

void TamperController::onDeviceConnected(QString MACAddress)
{
	tcDeviceList.append(new tcDevice);
	tcDeviceList.last()->MAC = MACAddress;

}


void TamperController::onDeviceDisconnected(QString MACAddress)
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