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
	tcDeviceList.append(new tcDevice);
	tcDeviceList.last()->MAC = MACAddress;
	tcDeviceList.last()->hasIPAddress = false;
	tcDeviceList.last()->divert = new PacketController();
	tcDeviceList.last()->divert->start();
	//tcDeviceList.last()->divert->divertStart(MACAddress, &tcDeviceList.last()->hasIPAddress);
	connect(this, &TamperController::packetControllerStart, tcDeviceList.last()->divert, &PacketController::onPacketControllerStart, Qt::QueuedConnection);
	emit packetControllerStart(MACAddress, &tcDeviceList.last()->hasIPAddress);
	
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
			d->divert->divertStop();
			delete d;
			break;
		}
	}
}


void TamperController::onCoreTamperStart(QString MACAddress, QString TamperType)
{
	/* Search through the tab list for the matching MAC address */

	for (tcDevice* d : tcDeviceList)
	{
		if (d->MAC == MACAddress)
		{
			/* Start tamper type */
			d->divert->drop->enabledFlag = 1;
		}
	}
}

void TamperController::onCoreTamperStop(QString MACAddress, QString TamperType)
{
	/* Search through the tab list for the matching MAC address */

	for (tcDevice* d : tcDeviceList)
	{
		if (d->MAC == MACAddress)
		{
			/* Stop tamper type */
			d->divert->drop->enabledFlag = 0;
		}
	}
}