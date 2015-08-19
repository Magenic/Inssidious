#include "TamperController.h"



TamperController::TamperController()
{
	//WinDivertController* test = new WinDivertController();
}

TamperController::~TamperController()
{

}

void TamperController::onCoreAddDevice(QString MACAddress)
{

	/* Create a tcDevice */

	tcDeviceList.append(new DivertController(MACAddress));


	/* Start the DivertController thread */

	tcDeviceList.last()->start();


}


void TamperController::onCoreDropDevice(QString MACAddress)
{

	/* Search through the tab list for the matching MAC address */

	for (DivertController* d : tcDeviceList)
	{
		if (d->MAC == MACAddress)
		{
			/* Delete from the list */

			tcDeviceList.removeOne(d);
			//d->stop();
			delete d;
			break;
		}
	}
}


void TamperController::onCoreTamperStart(QString MACAddress, TamperType tamperType)
{
	/* Search through the tab list for the matching MAC address */

	for (DivertController* d : tcDeviceList)
	{
		if (d->MAC == MACAddress)
		{
			/* Start tamper type */
			d->drop->enabledFlag = 1;
		}
	}
}

void TamperController::onCoreTamperStop(QString MACAddress, TamperType tamperType)
{
	/* Search through the tab list for the matching MAC address */

	for (DivertController* d : tcDeviceList)
	{
		if (d->MAC == MACAddress)
		{

			/* Stop tamper type */
			d->drop->enabledFlag = 0;
		}
	}
}