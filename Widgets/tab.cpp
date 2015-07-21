#include "tab.h"


Tab::Tab(QWidget* parent, QString MACaddress)
{
	/* Initialize tab palettes for the various states */

	tabPaletteActive.setBrush(QPalette::Background, QBrush(tabImageActive));
	tabPaletteActiveHover.setBrush(QPalette::Background, QBrush(tabImageActiveHover));
	tabPaletteActivePressed.setBrush(QPalette::Background, QBrush(tabImageActivePressed));
	tabPaletteInactive.setBrush(QPalette::Background, QBrush(tabImageInactive));
	tabPaletteInactiveHover.setBrush(QPalette::Background, QBrush(tabImageInactiveHover));
	tabPaletteInactivePressed.setBrush(QPalette::Background, QBrush(tabImageInactivePressed));


	/* Set the layout and initial settings for individual device tabs */

	this->setLayout(new QHBoxLayout());
	this->setAutoFillBackground(true);
	this->setPalette(tabPaletteInactive);
	this->setFixedWidth(200);
	this->setFixedHeight(82);
	this->setParent(parent);



	tabDeviceIconLabel.setFixedSize(32, 32);
	tabDeviceNameLabel.setFont(QFont("Segoe UI Semibold", 12));
	tabDeviceNameLabel.setText("New Device");
	tabDeviceNameLabel.setContentsMargins(10, 0, 0, 0);				/*indent text from device avatar*/


	this->layout()->addItem(new QSpacerItem(5, 0));
	this->layout()->addWidget(&tabDeviceIconLabel);
	this->layout()->addItem(new QSpacerItem(2, 0));
	this->layout()->addWidget(&tabDeviceNameLabel);
	this->layout()->addItem(new QSpacerItem(5, 0));
	this->layout()->addWidget(&tabTamperCount);


	tabTamperContainer = new QWidget();
	tabTamperContainer->setGeometry(200,					//698 pixels in from the left
		16,										//6 pixels plus the title bar height down from the top
		800 - 200 - 16 - 16,								//Use width of the png for qlabel width
		600 - 120 - 16 - 16);								//Use height of the png for qlabel height
	QPalette test;
	test.setBrush(QPalette::Background, 				//Initialize the Tabs palette background
		QBrush(Qt::red));						//With the tabs background image
	tabTamperContainer->setPalette(test);							//Set the palette 

	tabTamperContainer->setAutoFillBackground(true);		//Don't fill in a background color
	
	tabTamperContainer->setParent(parent);				//Display the widget on top of Inssidious widget
	
	tabTamperContainer->hide();


	MAC = MACaddress;

}


void Tab::select()
{
	this->setPalette(tabPaletteActive);
	this->tabTamperContainer->show();
	this->active = true;

}


void Tab::unselect()
{
	this->setPalette(tabPaletteInactive);
	this->tabTamperContainer->hide();
	this->active = false;

}


void Tab::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background() == tabPaletteActivePressed.background())
	{
		this->setPalette(tabPaletteActive);
	}
	else if (this->palette().background() == tabPaletteInactivePressed.background())
	{
		this->setPalette(tabPaletteInactive);
	}

	emit tabClicked(this);
}

void Tab::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background() == tabPaletteActive.background() || this->palette().background() == tabPaletteActiveHover.background())
		{
			this->setPalette(tabPaletteActivePressed);
		}
		else if (this->palette().background() == tabPaletteInactive.background() || this->palette().background() == tabPaletteInactiveHover.background())
		{
			this->setPalette(tabPaletteInactivePressed);
		}
	}
}


void Tab::enterEvent(QEvent *e)
{
	if (this->palette().background() == tabPaletteActive.background())
	{
		this->setPalette(tabPaletteActiveHover);
	}
	else if (this->palette().background() == tabPaletteInactive.background())
	{
		this->setPalette(tabPaletteInactiveHover);
	}
}


void Tab::leaveEvent(QEvent *e)
{
	if (this->palette().background() == tabPaletteActiveHover.background() || this->palette().background() == tabPaletteActivePressed.background())
	{
		this->setPalette(tabPaletteActive);
	}
	else if (this->palette().background() == tabPaletteInactiveHover.background() || this->palette().background() == tabPaletteInactivePressed.background())
	{
		this->setPalette(tabPaletteInactive);
	}
}