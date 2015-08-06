/*
*  File:		header.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "HeaderWidget.h"


HeaderWidget::HeaderWidget(QWidget *parent)
	: QWidget(parent)
{

	/* Initialize the menu palettes with background images for each state */

	menuPaletteDefault.setBrush(QPalette::Background, QBrush(menuDefault));
	menuPaletteHover.setBrush(QPalette::Background, QBrush(menuHover));
	menuPalettePressed.setBrush(QPalette::Background, QBrush(menuPressed));


	/* Draw the Inssidious Menu icon */

	this->setPalette(menuPaletteDefault);		//Set the palette to the default menu icon
	this->setGeometry(10,						//Start 10 pixels in from the left
		0,										//0 pixels from the top
		menuDefault.width(),					//Use width of the png for widget width 
		menuDefault.height());					//Use height of the png for widget height
	this->setAutoFillBackground(true);			//Fill the background since we're using background palettes
	this->setParent(parent);					//Display the widget on top of Inssidious widget


	/* Draw the Sid logo */

	//sid = new QLabel();							//Initialize the QLabel pointer
	//sid->setPixmap(sidPixmap);					//Set it to display the Sid logo
	//sid->setGeometry(698,						//698 pixels in from the left
	//	6 + GetSystemMetrics(SM_CYCAPTION),		//6 pixels plus the title bar height down from the top
	//	sidPixmap.width(),						//Use width of the png for qlabel width
	//	sidPixmap.height());					//Use height of the png for qlabel height
	//sid->setAutoFillBackground(false);			//Don't fill in a background color
	//sid->setParent(parent);						//Display the widget on top of Inssidious widget

	

	/* Draw the Minimize & Close icons */

	QPushButton *pushButtonMinimize = new QPushButton("", this);
	pushButtonMinimize->setObjectName("pushButtonMinimize");
	pushButtonMinimize->setGeometry(720,						//698 pixels in from the left
		6,		//6 pixels plus the title bar height down from the top
		14,						//Use width of the png for qlabel width
		14);					//Use height of the png for qlabel height
	pushButtonMinimize->setAutoFillBackground(true);			//Don't fill in a background color
	pushButtonMinimize->setParent(parent);						//Display the widget on top of Inssidious widget
	QObject::connect(pushButtonMinimize, SIGNAL(clicked()), this, SLOT(pushButtonMinimizeClicked()));

	// Close
	QPushButton *pushButtonClose = new QPushButton("", this);
	pushButtonClose->setObjectName("pushButtonClose");
	pushButtonClose->setGeometry(768,						//698 pixels in from the left
		6,		//6 pixels plus the title bar height down from the top
		14,						//Use width of the png for qlabel width
		14);					//Use height of the png for qlabel height
	pushButtonClose->setAutoFillBackground(true);			//Don't fill in a background color
	pushButtonClose->setParent(parent);						//Display the widget on top of Inssidious widget

	QObject::connect(pushButtonClose, SIGNAL(clicked()), this, SLOT(pushButtonCloseClicked()));


	/* To Do: Draw the wireless network name and password */

}



void HeaderWidget::enterEvent(QEvent *e)
{
	if (this->palette().background() == menuPaletteDefault.background())
	{
		this->setPalette(menuPaletteHover);
	}
}

void HeaderWidget::leaveEvent(QEvent *e)
{
	if (this->palette().background() == menuPaletteHover.background() || this->palette().background() == menuPalettePressed.background())
	{
		this->setPalette(menuPaletteDefault);
	}
}

void HeaderWidget::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background() == menuPalettePressed.background())
	{
		this->setPalette(menuPaletteDefault);
	}

	//emit menuClicked();
}

void HeaderWidget::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background() == menuPaletteDefault.background() || this->palette().background() == menuPaletteHover.background())
		{
			this->setPalette(menuPalettePressed);
		}
	}
}