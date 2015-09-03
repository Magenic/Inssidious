/*
*  File:		tabcontroller.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/

#include "UiDeviceController.h"
#include "Windows.h"

UiDeviceController::UiDeviceController(QWidget *parent)
	: QWidget(parent)
{

	/* Set the layout and initial settings for the Tabs side bar */

	this->setLayout(new QHBoxLayout());							//Use a Horizontal Box Layout to stack tabs left -> right
	this->layout()->setContentsMargins(0, 0, 0, 0);				//Zero margins for any child widget 
	this->layout()->setSpacing(0);								//Set spacing between child widgets to 0 pixels
	this->layout()->setAlignment(Qt::AlignLeft);				//Align the child widgets up against the left of the widget
	this->setAutoFillBackground(false);							//And enable filling in the  background
	this->setParent(parent);									//Display the widget on top of Inssidious widget
	this->setGeometry(10 /* in */, 64 /* down */, 480 /* width */, 44 /* height */);


}

UiDeviceController::~UiDeviceController()
{

}


//Receives notifications to create a tab when a device has connected
void UiDeviceController::onUiAddDevice(QString MACAddress)
{

	/* Create a new device */

	deviceList.append(new device(
		{
			MACAddress,
			new TabWidget(this),
			new TamperWidget(this),
			new NewDeviceWidget(this, MACAddress),
			false
		}
	));
	

	/* Add the Tab Widget to the UiDeviceController layout and connect the tabClicked signal */

	this->layout()->addWidget(deviceList.last()->tab);
	connect(deviceList.last()->tab, &TabWidget::tabClicked, this, &UiDeviceController::onTabClicked);


	/* Set the parent of the Tamper & New Device Widgets to the main InssidiousUi widget */

	deviceList.last()->tamper->setParent(this->parentWidget());
	deviceList.last()->newDevice->setParent(this->parentWidget());


	/* Connect signals and slots */

	connect(deviceList.last()->tamper, &TamperWidget::tamperStart, this, &UiDeviceController::onTamperStart);
	connect(deviceList.last()->tamper, &TamperWidget::tamperStop, this, &UiDeviceController::onTamperStop);
	connect(deviceList.last()->newDevice, &NewDeviceWidget::setDeviceInfo, this, &UiDeviceController::onSetDeviceInfo);


	/* Check if the NewDeviceWidget already knew about this device */

	if(deviceList.last()->newDevice->knownDevice)
	{

		/* Update the tab and tamper widgets */

		deviceList.last()->tab->setName(deviceList.last()->newDevice->knownDeviceName);
		deviceList.last()->tamper->setImage(deviceList.last()->newDevice->knownDeviceType);
		
		deviceList.last()->named = true;
	}


	/* If this is the first tab we've added, select it to default it to active */

	if (deviceList.count() == 1) 
	{
		deviceList.last()->tab->select();
		deviceList.last()->tab->lower();

		if (deviceList.last()->named)
		{
			deviceList.last()->tamper->show();
			deviceList.last()->tamper->lower();
		}
		else
		{
			deviceList.last()->newDevice->show();
			deviceList.last()->newDevice->lower();
		}
		
	}

}


//Receive notifications to delete a tab when a device has disconnected
void UiDeviceController::onUiDropDevice(QString MACAddress)
{

	/* Search through the tab list for the matching MAC address */

	for (device* d : deviceList)
	{
		if (d->MAC == MACAddress)
		{
			/* Delete the tab and remove it from the tab list */

			/* If the tab was selected we additionally need to set the remaining topmost tab as selected */

			if (d->tab->selected && deviceList.count() != 1)
			{
				deviceList.removeOne(d);
				d->tab->deleteLater();
				d->tamper->deleteLater();
				d->newDevice->deleteLater();
				deviceList.first()->tab->select();
				deviceList.first()->tamper->show();
				break;
			}
			else
			{
				deviceList.removeOne(d);
				d->tab->deleteLater();
				d->tamper->deleteLater();
				d->newDevice->deleteLater();
				break;
			}
		}
	}
}


//Receive notifications to switch to a different active tab
void UiDeviceController::onTabClicked(TabWidget* tab)
{
	/* Unselect all tabs, then select the one that was clicked */

	for (device* d : deviceList)
	{
		if (d->tab == tab)
		{
			tab->select();
			if (d->named)
			{
				d->tamper->show();
			}
			else
			{
				d->newDevice->show();
			}
		}
		else
		{
			d->tab->unselect();
			if (d->named)
			{
				d->tamper->hide();
			}
			else
			{
				d->newDevice->hide();
			}
		}
	}
}

void UiDeviceController::onTamperStart(TamperWidget* signaled, TamperType type, void * pTamperConfig)
{

	for (device* d : deviceList)
	{
		if (d->tamper == signaled)
		{
			emit uiTamperStart(d->MAC, TamperType(type), pTamperConfig);
			return;
		}
	}
}

void UiDeviceController::onTamperStop(TamperWidget* signaled, TamperType type)
{

	for (device* d : deviceList)
	{
		if (d->tamper == signaled)
		{
			emit uiTamperStop(d->MAC, TamperType(type));
			return;
		}
	}
}


void UiDeviceController::onSetDeviceInfo(QString MACAddress, QString deviceName, QString deviceType)
{
	for (device* d : deviceList)
	{
		if (d->MAC == MACAddress)
		{
			d->named = true;

			/* Hide the new device widget */

			d->newDevice->hide();

			/* Show the tamper widget and update the tab widget */

			d->tab->setName(deviceName);
			d->tamper->setImage(deviceType);
			d->tamper->show();

			return;
		}
	}
}