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


void TabController::onDeviceConnected(QString MACaddress)
{

	/* Add a new Tab to the list and layout, then connect the tabClicked signal */
	
	tcTabList.append(new Tab(this, MACaddress));
	this->layout()->addWidget(tcTabList.last());
	connect(tcTabList.last(), &Tab::tabClicked, 
		this, &TabController::onTabClicked);


	/* If this is the first tab we've added, select it to default it to active and change the background image */

	if (tcTabList.count() == 1) 
	{
		tcTabList.last()->select();
		this->setPalette(tcPaletteDevicesPresent);
	}

}


void TabController::onDeviceDisconnected(QString MACAddress)
{

	for (Tab* t : tcTabList)
	{
		if (t->MAC == MACAddress)
		{
			if (t->active)
			{
				tcTabList.removeOne(t);
				t->deleteLater();
				tcTabList.first()->select();
				break;
			}
			else
			{
				tcTabList.removeOne(t);
				t->deleteLater();
				break;
			}
		}
	}


	/* If the tab list is now empty, switch to the no devices present background image */

	if (tcTabList.isEmpty())
	{
		this->setPalette(tcPaletteNoDevices);
	}

}


void TabController::onTabClicked(Tab* tab)
{
	for (Tab* t : tcTabList)
	{
		t->unselect();
	}

	tab->select();
}