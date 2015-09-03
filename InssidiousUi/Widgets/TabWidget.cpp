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
	this->setFixedWidth(146);
	this->setFixedHeight(44);
	this->setParent(parent);


	tabDeviceIconLabel.setFixedSize(32, 32);
	QFont tabNameFont;
	QPalette tabNamePalette;

	tabNamePalette.setColor(QPalette::WindowText, QColor(255, 255, 255));
	//moduleTextPaletteInactive.setColor(QPalette::WindowText, QColor(83, 84, 85));

	tabNameFont.setFamily("Segoe UI");
	//tabNameFont.setWeight(QFont::DemiBold);
	tabNameFont.setPixelSize(15);
	tabNameFont.setStyleStrategy(QFont::PreferAntialias);


	tabDeviceNameLabel.setFont(tabNameFont);
	tabDeviceNameLabel.setText("New Device");
	tabDeviceNameLabel.setPalette(tabNamePalette);
	tabDeviceNameLabel.setContentsMargins(0, 0, 0, 0);
	tabDeviceNameLabel.setAlignment(Qt::AlignCenter);


	//this->layout()->addItem(new QSpacerItem(5, 0));
	//this->layout()->addWidget(&tabDeviceIconLabel);
	//this->layout()->addItem(new QSpacerItem(2, 0));
	this->layout()->setAlignment(Qt::AlignHCenter);
	this->layout()->addWidget(&tabDeviceNameLabel);
	//this->layout()->addItem(new QSpacerItem(5, 0));
	//this->layout()->addWidget(&tabTamperCount);


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

void TabWidget::setName(QString name)
{
	this->tabDeviceNameLabel.setText(name);

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