/*
*  File:		tabcontroller.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "tabcontroller.h"

TabController::TabController(QWidget *parent)
	: QWidget(parent)
{

	/* Set the layout and initial settings for the Tabs side bar */

	this->setLayout(new QVBoxLayout());							//Use a Vertical Box Layout to stack tabs top -> down
	this->layout()->setContentsMargins(0, 20, 0, 0);			//Zero margins for any child widget margins except for a 20 pixel pad from the top
	this->layout()->setSpacing(8);								//Set spacing between child widgets to 8 pixels
	this->layout()->setAlignment(Qt::AlignTop);					//Align the child widgets up against the the top of the widget
	this->setGeometry(16,										//Start 16 pixels in from the left to account for extended frame 
		120,													//120 pixels from the top to draw below the header and logo
		800 - 16,												//Use a wide, full window width so we can draw a background image
		600 - 120);												//Use height of the parent minus our padding down from the top
	tcPaletteDevicesPresent.setBrush(QPalette::Background,		//Set a background image for the devices present palette
		QBrush(tcBackgroundImageDevicesPresent));				//With the tab container area background image
	tcPaletteNoDevices.setBrush(QPalette::Background,			//Set a background image for the no devices present palette
		QBrush(tcBackgroundImageNoDevices));					//With the no devices present background image
	this->setPalette(tcPaletteNoDevices);						//Set the palette as no devices present
	this->setAutoFillBackground(true);							//And enable filling in the  background
	this->setParent(parent);									//Display the widget on top of Inssidious widget


}

TabController::~TabController()
{

}


//Receives notifications to create a tab when a device has connected
void TabController::onDeviceConnected(QString MACAddress)
{

	/* Add a new Tab to the list and layout, then connect the tabClicked signal */
	
	tcDeviceList.append(new tcDevice);
	tcDeviceList.last()->MAC = MACAddress;
	tcDeviceList.last()->tab = new Tab(this);
	tcDeviceList.last()->tbContainer = new QWidget(this);
	tcDeviceList.last()->tbGridLayout = new QGridLayout();
	tcDeviceList.last()->tb1 = new TamperButton(tcDeviceList.last()->tbContainer);
	tcDeviceList.last()->tb2 = new TamperButton(tcDeviceList.last()->tbContainer);
	tcDeviceList.last()->tb3 = new TamperButton(tcDeviceList.last()->tbContainer);
	tcDeviceList.last()->tb4 = new TamperButton(tcDeviceList.last()->tbContainer);
	tcDeviceList.last()->tb5 = new TamperButton(tcDeviceList.last()->tbContainer);
	tcDeviceList.last()->tb6 = new TamperButton(tcDeviceList.last()->tbContainer);
	tcDeviceList.last()->tb7 = new TamperButton(tcDeviceList.last()->tbContainer);
	tcDeviceList.last()->tb8 = new TamperButton(tcDeviceList.last()->tbContainer);


	this->layout()->addWidget(tcDeviceList.last()->tab);
	

	
	tcDeviceList.last()->tbContainer->setLayout(tcDeviceList.last()->tbGridLayout);									//Use a Vertical Box Layout to stack tabs top -> down
	tcDeviceList.last()->tbContainer->setGeometry(200,										//698 pixels in from the left
		16,														//6 pixels plus the title bar height down from the top
		800 - 200 - 16 - 16,									//Use width of the png for qlabel width
		600 - 120 - 16 - 16);									//Use height of the png for qlabel height
	tcDeviceList.last()->tbContainer->setAutoFillBackground(false);							//Don't fill in a background color
	tcDeviceList.last()->tbContainer->setParent(this);					//Display the widget on top of Inssidious widget


	tcDeviceList.last()->tbGridLayout->setContentsMargins(0, 0, 0, 0);				//Zero margins for any child widget margins except for a 20 pixel pad from the top
	tcDeviceList.last()->tbGridLayout->setSpacing(0);								//Set spacing between child widgets to 8 pixels
	tcDeviceList.last()->tbGridLayout->addWidget(tcDeviceList.last()->tb1, 0, 0);
	tcDeviceList.last()->tbGridLayout->addWidget(tcDeviceList.last()->tb2, 0, 1);
	tcDeviceList.last()->tbGridLayout->addWidget(tcDeviceList.last()->tb3, 1, 0);
	tcDeviceList.last()->tbGridLayout->addWidget(tcDeviceList.last()->tb4, 1, 1);
	tcDeviceList.last()->tbGridLayout->addWidget(tcDeviceList.last()->tb5, 2, 0);
	tcDeviceList.last()->tbGridLayout->addWidget(tcDeviceList.last()->tb6, 2, 1);
	tcDeviceList.last()->tbGridLayout->addWidget(tcDeviceList.last()->tb7, 3, 0);
	tcDeviceList.last()->tbGridLayout->addWidget(tcDeviceList.last()->tb8, 3, 1);


	connect(tcDeviceList.last()->tab, &Tab::tabClicked, this, &TabController::onTabClicked);

	connect(tcDeviceList.last()->tb1, &TamperButton::tamperButtonClicked, this, &TabController::onTamperButtonClicked);
	connect(tcDeviceList.last()->tb2, &TamperButton::tamperButtonClicked, this, &TabController::onTamperButtonClicked);
	connect(tcDeviceList.last()->tb3, &TamperButton::tamperButtonClicked, this, &TabController::onTamperButtonClicked);
	connect(tcDeviceList.last()->tb4, &TamperButton::tamperButtonClicked, this, &TabController::onTamperButtonClicked);
	connect(tcDeviceList.last()->tb5, &TamperButton::tamperButtonClicked, this, &TabController::onTamperButtonClicked);
	connect(tcDeviceList.last()->tb6, &TamperButton::tamperButtonClicked, this, &TabController::onTamperButtonClicked);
	connect(tcDeviceList.last()->tb7, &TamperButton::tamperButtonClicked, this, &TabController::onTamperButtonClicked);
	connect(tcDeviceList.last()->tb8, &TamperButton::tamperButtonClicked, this, &TabController::onTamperButtonClicked);


	/* If this is the first tab we've added, select it to default it to active and change the background image */

	if (tcDeviceList.count() == 1) 
	{
		tcDeviceList.last()->tab->select();
		tcDeviceList.last()->tbContainer->show();
		this->setPalette(tcPaletteDevicesPresent);
	}

}


//Receive notifications to delete a tab when a device has disconnected
void TabController::onDeviceDisconnected(QString MACAddress)
{

	/* Search through the tab list for the matching MAC address */

	for (tcDevice* d : tcDeviceList)
	{
		if (d->MAC == MACAddress)
		{
			/* Delete the tab and remove it from the tab list */

			/* If the tab was selected we additionally need to set the remaining topmost tab as selected */

			if (d->tab->selected && tcDeviceList.count() != 1)
			{
				tcDeviceList.removeOne(d);
				d->tab->deleteLater();
				d->tbContainer->deleteLater();
				tcDeviceList.first()->tab->select();
				break;
			}
			else
			{
				tcDeviceList.removeOne(d);
				d->tab->deleteLater();
				d->tbContainer->deleteLater();
				break;
			}
		}
	}


	/* If the tab list is now empty, switch to the no devices present background image */

	if (tcDeviceList.isEmpty())
	{
		this->setPalette(tcPaletteNoDevices);
	}

}


//Receive notifications to switch to a different active tab
void TabController::onTabClicked(Tab* tab)
{
	/* Unselect all tabs, then select the one that was clicked */

	for (tcDevice* d : tcDeviceList)
	{
		if (d->tab == tab)
		{
			tab->select();
			d->tbContainer->show();
		}
		else
		{
			d->tab->unselect();
			d->tbContainer->hide();
		}
	}
}

void TabController::onTamperButtonClicked(TamperButton* tamperButton)
{
	if (tamperButton->selected)
	{
		/* TODO: Send blocking? signals up the chain */
		/* Ah. How about an inbetween state of changing... */

		/* Change state of button */
		tamperButton->unselect();
	}
	else
	{
		/* TODO: Send blocking? signals up the chain */
		/* Ah. How about an inbetween state of changing... */

		/* Change state of button */

		tamperButton->select();
	}
}