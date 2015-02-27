#include "startupwidget.h"

StartupWidget::StartupWidget(QWidget *parent)
	: QWidget(parent)
{
	//Initialize the layout for StartupWidget
	startupWidgetLayout = new QGridLayout();
	startupWidgetLayout->setSpacing(0);
	startupWidgetLayout->setContentsMargins(225, 120, 225, 0);

	//Draw the Inssidious logo and add it to the layout
	inssidiousLogo = new QLabel();
	inssidiousLogo->setPixmap(QPixmap(":/StartupWidget/AppLogo.png"));
	inssidiousLogo->setContentsMargins(0, 0, 0, 10); /* padding */
	startupWidgetLayout->addWidget(inssidiousLogo, 0, 0, Qt::AlignTop);

	//Draw the remaining StartupWidget fields
	// ????
	// ????
	// ????
	// ????

	//Set the layout for StartupWidget
	this->setLayout(startupWidgetLayout);

	//Set the size policy and size of StartupWidget
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setMinimumSize(762, 644);

	//Set the background color of the StartupWidget to a grey black
	QPalette startupWidgetPalette(palette());
	startupWidgetPalette.setColor(QPalette::Background, QColor(42,42,42,255));
	this->setAutoFillBackground(true);
	this->setPalette(startupWidgetPalette);

	//Enable mouse tracking for hover highlighting on the sidebar
	this->setMouseTracking(true);
}

void StartupWidget::onCoreStarted()
{
	//Get network adapter info

	//Fill in 

}

void StartupWidget::onCoreFailedToStart(QString errorMessage)
{
	//Show error
}

void StartupWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void StartupWidget::mousePressEvent(QMouseEvent *e)
{

}

void StartupWidget::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void StartupWidget::contextMenuEvent(QContextMenuEvent *e)
{

}

void StartupWidget::enterEvent(QEvent *e)
{

}

void StartupWidget::leaveEvent(QEvent *e)
{

}