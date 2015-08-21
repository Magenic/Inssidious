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

	tamperClassFont.setPixelSize(16);
	tamperClassFont.setFamily("Calibri");
	tamperClassFont.setBold(true);
	tamperClassFont.setStyleStrategy(QFont::PreferAntialias);
}

TabController::~TabController()
{

}


//Receives notifications to create a tab when a device has connected
void TabController::onUiAddDevice(QString MACAddress)
{

	/* Create a new tcDevice */

	tcDeviceList.append(new tcDevice({
		MACAddress, 
		new TabWidget(this), 
		new QWidget(this), 
		new QVBoxLayout(),
		{
			new QLabel(TamperClassName[SPEED]),
			new QLabel(TamperClassName[NOISE]),
			new QLabel(TamperClassName[FAILURE]),
			new QLabel(TamperClassName[RESTRICTION])
		},
		{
			new QHBoxLayout(),
			new QHBoxLayout(),
			new QHBoxLayout(),
			new QHBoxLayout()
		},
		{
			new TamperWidget(LAG),
			new TamperWidget(THROTTLE),
			new TamperWidget(RESET),
			new TamperWidget(JITTER),
			new TamperWidget(DROPPED_PACKETS),
			new TamperWidget(CORRUPT_PACKETS),
			new TamperWidget(NO_PACKETS),
			new TamperWidget(NO_DNS),
			new TamperWidget(NO_SERVER),
			new TamperWidget(NO_SSL),
			new TamperWidget(REDIR_TO_PORTAL),
			new TamperWidget(HTTP_HTTPS_ONLY),
			new TamperWidget(SITE_BLOCKED)
		}
	}));
	

	/* Add the Tab Widget to the TabController layout and connect the tabClicked signal */

	this->layout()->addWidget(tcDeviceList.last()->tab);
	connect(tcDeviceList.last()->tab, &TabWidget::tabClicked, this, &TabController::onTabClicked);


	/* Initialize the Tamper Widget Container */

	tcDeviceList.last()->twContainer->setAutoFillBackground(false);
	tcDeviceList.last()->twContainer->setGeometry(200,								
		16,																				
		800 - 200 - 16 - 16,															
		600 - 120 - 16 - 16);																				
	tcDeviceList.last()->twContainer->setLayout(tcDeviceList.last()->twContainerVLayout);
	tcDeviceList.last()->twContainerVLayout->setContentsMargins(0, 0, 0, 0);
	tcDeviceList.last()->twContainerVLayout->setSpacing(0);	

	/* Set the widget parent values to allow hiding and showing the container */
	
	tcDeviceList.last()->twContainer->setParent(this);							
	tcDeviceList.last()->tamperWidget[LAG]->setParent(this);
	tcDeviceList.last()->tamperWidget[THROTTLE]->setParent(this);
	tcDeviceList.last()->tamperWidget[RESET]->setParent(this);
	tcDeviceList.last()->tamperWidget[JITTER]->setParent(this);
	tcDeviceList.last()->tamperWidget[DROPPED_PACKETS]->setParent(this);
	tcDeviceList.last()->tamperWidget[CORRUPT_PACKETS]->setParent(this);
	tcDeviceList.last()->tamperWidget[NO_PACKETS]->setParent(this);
	tcDeviceList.last()->tamperWidget[NO_DNS]->setParent(this);
	tcDeviceList.last()->tamperWidget[NO_SERVER]->setParent(this);
	tcDeviceList.last()->tamperWidget[NO_SSL]->setParent(this);
	tcDeviceList.last()->tamperWidget[REDIR_TO_PORTAL]->setParent(this);
	tcDeviceList.last()->tamperWidget[HTTP_HTTPS_ONLY]->setParent(this);
	tcDeviceList.last()->tamperWidget[SITE_BLOCKED]->setParent(this);



	/* Add the Tamper Class Labels and Layouts to the container */

	tcDeviceList.last()->twContainerVLayout->addWidget(tcDeviceList.last()->tamperClassLabel[SPEED], Qt::AlignHCenter);
	tcDeviceList.last()->twContainerVLayout->addLayout(tcDeviceList.last()->tamperClassLayout[SPEED], Qt::AlignHCenter);
	tcDeviceList.last()->twContainerVLayout->addWidget(tcDeviceList.last()->tamperClassLabel[NOISE], Qt::AlignHCenter);
	tcDeviceList.last()->twContainerVLayout->addLayout(tcDeviceList.last()->tamperClassLayout[NOISE], Qt::AlignHCenter);
	tcDeviceList.last()->twContainerVLayout->addWidget(tcDeviceList.last()->tamperClassLabel[FAILURE], Qt::AlignHCenter);
	tcDeviceList.last()->twContainerVLayout->addLayout(tcDeviceList.last()->tamperClassLayout[FAILURE], Qt::AlignHCenter);
	tcDeviceList.last()->twContainerVLayout->addWidget(tcDeviceList.last()->tamperClassLabel[RESTRICTION], Qt::AlignHCenter);
	tcDeviceList.last()->twContainerVLayout->addLayout(tcDeviceList.last()->tamperClassLayout[RESTRICTION], Qt::AlignHCenter);

	
	/* Set the Tamper Class Font and Alignment */

	tcDeviceList.last()->tamperClassLabel[SPEED]->setFont(tamperClassFont);
	tcDeviceList.last()->tamperClassLabel[NOISE]->setFont(tamperClassFont);
	tcDeviceList.last()->tamperClassLabel[FAILURE]->setFont(tamperClassFont);
	tcDeviceList.last()->tamperClassLabel[RESTRICTION]->setFont(tamperClassFont);
	tcDeviceList.last()->tamperClassLabel[SPEED]->setAlignment(Qt::AlignCenter);
	tcDeviceList.last()->tamperClassLabel[NOISE]->setAlignment(Qt::AlignCenter);
	tcDeviceList.last()->tamperClassLabel[FAILURE]->setAlignment(Qt::AlignCenter);
	tcDeviceList.last()->tamperClassLabel[RESTRICTION]->setAlignment(Qt::AlignCenter);

	/* Add the Tamper Types to the appropriate class layouts */

	tcDeviceList.last()->tamperClassLayout[SPEED]->addWidget(tcDeviceList.last()->tamperWidget[LAG]);
	tcDeviceList.last()->tamperClassLayout[SPEED]->addWidget(tcDeviceList.last()->tamperWidget[THROTTLE]);

	tcDeviceList.last()->tamperClassLayout[NOISE]->addWidget(tcDeviceList.last()->tamperWidget[RESET]);
	tcDeviceList.last()->tamperClassLayout[NOISE]->addWidget(tcDeviceList.last()->tamperWidget[JITTER]);
	tcDeviceList.last()->tamperClassLayout[NOISE]->addWidget(tcDeviceList.last()->tamperWidget[DROPPED_PACKETS]);
	tcDeviceList.last()->tamperClassLayout[NOISE]->addWidget(tcDeviceList.last()->tamperWidget[CORRUPT_PACKETS]);

	tcDeviceList.last()->tamperClassLayout[FAILURE]->addWidget(tcDeviceList.last()->tamperWidget[NO_PACKETS]);
	tcDeviceList.last()->tamperClassLayout[FAILURE]->addWidget(tcDeviceList.last()->tamperWidget[NO_DNS]);
	tcDeviceList.last()->tamperClassLayout[FAILURE]->addWidget(tcDeviceList.last()->tamperWidget[NO_SERVER]);
	tcDeviceList.last()->tamperClassLayout[FAILURE]->addWidget(tcDeviceList.last()->tamperWidget[NO_SSL]);

	tcDeviceList.last()->tamperClassLayout[RESTRICTION]->addWidget(tcDeviceList.last()->tamperWidget[REDIR_TO_PORTAL]);
	tcDeviceList.last()->tamperClassLayout[RESTRICTION]->addWidget(tcDeviceList.last()->tamperWidget[HTTP_HTTPS_ONLY]);
	tcDeviceList.last()->tamperClassLayout[RESTRICTION]->addWidget(tcDeviceList.last()->tamperWidget[SITE_BLOCKED]);


	




	
	connect(tcDeviceList.last()->tamperWidget[LAG], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[THROTTLE], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[RESET], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[JITTER], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[DROPPED_PACKETS], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[CORRUPT_PACKETS], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[NO_PACKETS], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[NO_DNS], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[NO_SERVER], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[NO_SSL], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[REDIR_TO_PORTAL], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[HTTP_HTTPS_ONLY], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);
	connect(tcDeviceList.last()->tamperWidget[SITE_BLOCKED], &TamperWidget::tamperButtonClicked, this, &TabController::onTamperWidgetClicked);

	/* If this is the first tab we've added, select it to default it to active and change the background image */

	if (tcDeviceList.count() == 1) 
	{
		tcDeviceList.last()->tab->select();
		tcDeviceList.last()->twContainer->show();
		this->setPalette(tcPaletteDevicesPresent);
	}

}


//Receive notifications to delete a tab when a device has disconnected
void TabController::onUiDropDevice(QString MACAddress)
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
				d->twContainer->deleteLater();
				tcDeviceList.first()->tab->select();
				tcDeviceList.first()->twContainer->show();
				break;
			}
			else
			{
				tcDeviceList.removeOne(d);
				d->tab->deleteLater();
				d->twContainer->deleteLater();
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

void TabController::onUiTamperStarted(QString MACAddress, TamperType tamperType)
{

}

void TabController::onUiTamperStopped(QString MACAddress, TamperType tamperType)
{

}

//Receive notifications to switch to a different active tab
void TabController::onTabClicked(TabWidget* tab)
{
	/* Unselect all tabs, then select the one that was clicked */

	for (tcDevice* d : tcDeviceList)
	{
		if (d->tab == tab)
		{
			tab->select();
			d->twContainer->show();
		}
		else
		{
			d->tab->unselect();
			d->twContainer->hide();
		}
	}
}

void TabController::onTamperWidgetClicked(TamperWidget* tamperWidget)
{

	for (tcDevice* d : tcDeviceList)
	{
		for (int i = 0; i < NUM_TAMPER_TYPES - 1; i++)
		{
			if (d->tamperWidget[i] == tamperWidget)
			{
				if (d->tamperWidget[i]->selected)
				{
					emit uiTamperStop(d->MAC, TamperType(i));
					d->tamperWidget[i]->unselect();
				}
				else
				{
					emit uiTamperStart(d->MAC, TamperType(i));
					d->tamperWidget[i]->select();
				}
			}
		}
	}
}