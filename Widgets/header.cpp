/*
*  File:		header.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "header.h"


Header::Header(QWidget *parent)
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

	sid = new QLabel();							//Initialize the QLabel pointer
	sid->setPixmap(sidPixmap);					//Set it to display the Sid logo
	sid->setGeometry(698,						//698 pixels in from the left
		6 + GetSystemMetrics(SM_CYCAPTION),		//6 pixels plus the title bar height down from the top
		sidPixmap.width(),						//Use width of the png for qlabel width
		sidPixmap.height());					//Use height of the png for qlabel height
	sid->setAutoFillBackground(false);			//Don't fill in a background color
	sid->setParent(parent);						//Display the widget on top of Inssidious widget


	/* To Do: Draw the wireless network name and password */

}

Header::~Header()
{

}



void Header::enterEvent(QEvent *e)
{
	if (this->palette().background() == menuPaletteDefault.background())
	{
		this->setPalette(menuPaletteHover);
	}
}

void Header::leaveEvent(QEvent *e)
{
	if (this->palette().background() == menuPaletteHover.background() || this->palette().background() == menuPalettePressed.background())
	{
		this->setPalette(menuPaletteDefault);
	}
}

void Header::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background() == menuPalettePressed.background())
	{
		this->setPalette(menuPaletteDefault);
	}

	//emit menuClicked();
}

void Header::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background() == menuPaletteDefault.background() || this->palette().background() == menuPaletteHover.background())
		{
			this->setPalette(menuPalettePressed);
		}
	}
}