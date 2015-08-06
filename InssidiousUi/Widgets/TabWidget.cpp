/*
*  File:		tab.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "TabWidget.h"


TabWidget::TabWidget(QWidget* parent)
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


}


void TabWidget::select()
{
	this->setPalette(tabPaletteActive);
	this->selected = true;

}


void TabWidget::unselect()
{
	this->setPalette(tabPaletteInactive);
	this->selected = false;

}


void TabWidget::mouseReleaseEvent(QMouseEvent *e)
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

void TabWidget::mousePressEvent(QMouseEvent *e)
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


void TabWidget::enterEvent(QEvent *e)
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


void TabWidget::leaveEvent(QEvent *e)
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