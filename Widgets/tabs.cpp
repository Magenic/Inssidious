#include "tabs.h"

Tabs::Tabs(QWidget *parent)
	: QWidget(parent)
{
	/* Set the layout and initial settings for the Start widget */

	this->setLayout(new QVBoxLayout());							//Use a Vertical Box Layout
	this->layout()->setContentsMargins(0, 12, 0, 0);			//Clear the content margins except for a 12 pixel pad from the top
	this->layout()->setSpacing(12);								//Clear the spacing between any child widgets
	this->layout()->setAlignment(Qt::AlignTop);					//Align layout contents at the top of the widget
	this->setGeometry(16,										//Start 16 pixels in from the left to account for extended frame 
		120,													//120 pixels from the top to draw below the header and logo
		200,													//200 pixels as a fixed width for the sidebar
		600 - 120);												//Use height of the parent - padding 
	this->setAutoFillBackground(false);							//Don't fill in a background color
	this->setParent(parent);									//Display the widget on top of Inssidious widget

	
}


Tabs::~Tabs()
{

}


void Tabs::addTab()
{
	tabList.append(new Tab(this));
	
	this->layout()->addWidget(tabList.last());
}


void Tabs::removeTab()
{
	tabList.removeFirst();
}


Tab::Tab(QWidget* parent)
{

	//Set the device widget background to a dark grey
	this->setAutoFillBackground(true);
	this->setPalette(QPalette(QPalette::Background, QColor(65, 65, 65, 255)));

	//Set the device widget size
	this->setFixedWidth(200);
	this->setFixedHeight(82);

	//Set Parent
	this->setParent(parent);

	//Initialize Colors for Device Name and Device Widget Background
	textColorActive = QColor(255, 255, 255, 255);
	textColorInactive = QColor(65, 65, 65, 255);
	backgroundColorActive = QColor(255, 255, 255, 255);
	backgroundColorActiveHover = QColor(245, 245, 245, 255);
	backgroundColorActivePressed = QColor(235, 235, 235, 255);
	backgroundColorInactive = QColor(65, 65, 65, 255);
	backgroundColorInactiveHover = QColor(75, 75, 75, 255);
	backgroundColorInactivePressed = QColor(85, 85, 85, 255);
}

void Tab::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background().color() == backgroundColorActivePressed)
	{
		this->setPalette(backgroundColorActive);
	}
	else if (this->palette().background().color() == backgroundColorInactivePressed)
	{
		this->setPalette(backgroundColorInactive);
	}

	emit tabClicked(this);
}

void Tab::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background().color() == backgroundColorActive || this->palette().background().color() == backgroundColorActiveHover)
		{
			this->setPalette(backgroundColorActivePressed);
		}
		else if (this->palette().background().color() == backgroundColorInactive || this->palette().background().color() == backgroundColorInactiveHover)
		{
			this->setPalette(backgroundColorInactivePressed);
		}
	}
}


void Tab::enterEvent(QEvent *e)
{
	if (this->palette().background().color() == backgroundColorActive)
	{
		this->setPalette(backgroundColorActiveHover);
	}
	else if (this->palette().background().color() == backgroundColorInactive)
	{
		this->setPalette(backgroundColorInactiveHover);
	}
}

void Tab::leaveEvent(QEvent *e)
{
	if (this->palette().background().color() == backgroundColorActiveHover || this->palette().background().color() == backgroundColorActivePressed)
	{
		this->setPalette(backgroundColorActive);
	}
	else if (this->palette().background().color() == backgroundColorInactiveHover || this->palette().background().color() == backgroundColorInactivePressed)
	{
		this->setPalette(backgroundColorInactive);
	}
}