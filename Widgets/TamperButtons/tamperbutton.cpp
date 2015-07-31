#include "tamperbutton.h"

TamperButton::TamperButton(QWidget *parent)
	: QWidget(parent)
{
	/* Initialize tamper palettes for the various states */

	tamperPaletteActive.setBrush(QPalette::Background, QBrush(tamperImageActive));
	tamperPaletteActiveHover.setBrush(QPalette::Background, QBrush(tamperImageActiveHover));
	tamperPaletteActivePressed.setBrush(QPalette::Background, QBrush(tamperImageActivePressed));
	tamperPaletteInactive.setBrush(QPalette::Background, QBrush(tamperImageInactive));
	tamperPaletteInactiveHover.setBrush(QPalette::Background, QBrush(tamperImageInactiveHover));
	tamperPaletteInactivePressed.setBrush(QPalette::Background, QBrush(tamperImageInactivePressed));


	/* Set the layout and initial settings for individual device tampers */

	this->setLayout(new QHBoxLayout());
	this->setAutoFillBackground(true);
	this->setPalette(tamperPaletteInactive);
	this->setFixedWidth(250);
	this->setFixedHeight(80);
	this->setParent(parent);

	this->selected = false;
}

TamperButton::~TamperButton()
{

}


void TamperButton::select()
{
	this->setPalette(tamperPaletteActive);
	this->selected = true;
}


void TamperButton::unselect()
{
	this->setPalette(tamperPaletteInactive);
	this->selected = false;
}


void TamperButton::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background() == tamperPaletteActivePressed.background())
	{
		this->setPalette(tamperPaletteActive);
	}
	else if (this->palette().background() == tamperPaletteInactivePressed.background())
	{
		this->setPalette(tamperPaletteInactive);
	}

	emit tamperButtonClicked(this);
}

void TamperButton::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background() == tamperPaletteActive.background() || this->palette().background() == tamperPaletteActiveHover.background())
		{
			this->setPalette(tamperPaletteActivePressed);
		}
		else if (this->palette().background() == tamperPaletteInactive.background() || this->palette().background() == tamperPaletteInactiveHover.background())
		{
			this->setPalette(tamperPaletteInactivePressed);
		}
	}
}


void TamperButton::enterEvent(QEvent *e)
{
	if (this->palette().background() == tamperPaletteActive.background())
	{
		this->setPalette(tamperPaletteActiveHover);
	}
	else if (this->palette().background() == tamperPaletteInactive.background())
	{
		this->setPalette(tamperPaletteInactiveHover);
	}
}


void TamperButton::leaveEvent(QEvent *e)
{
	if (this->palette().background() == tamperPaletteActiveHover.background() || this->palette().background() == tamperPaletteActivePressed.background())
	{
		this->setPalette(tamperPaletteActive);
	}
	else if (this->palette().background() == tamperPaletteInactiveHover.background() || this->palette().background() == tamperPaletteInactivePressed.background())
	{
		this->setPalette(tamperPaletteInactive);
	}
}