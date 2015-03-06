#include "devicewidget.h"

DeviceWidget::DeviceWidget(DeviceType)
{
	//Enable mouse tracking for hover highlighting on the sidebar
	this->setMouseTracking(true);

	//Set the device widget background to a dark grey
	this->setAutoFillBackground(true);
	this->setPalette(QPalette(QPalette::Background, QColor(65, 65, 65, 255)));

	//Set the device widget size
	this->setFixedWidth(210);
	this->setFixedHeight(50);

	//Zero the layout spacing & margin and set layout for the device widget
	deviceWidgetLayout.setSpacing(0);
	deviceWidgetLayout.setMargin(0);
	this->setLayout(&deviceWidgetLayout);

	//Initialize the Device Name font
	deviceNameFont.setPointSize(15);
	deviceNameFont.setFamily("Calibri");
	deviceNameFont.setBold(true);

	//Initialize Colors for Device Name and Device Widget Background
	textColorActive = QColor(255, 255, 255, 255); 
	textColorInactive = QColor(65, 65, 65, 255);
	backgroundColorActive = QColor(255, 255, 255, 255);
	backgroundColorActiveHover = QColor(245, 245, 245, 255);
	backgroundColorActivePressed = QColor(235, 235, 235, 255);
	backgroundColorInactive = QColor(65, 65, 65, 255);
	backgroundColorInactiveHover = QColor(75, 75, 75, 255);
	backgroundColorInactivePressed = QColor(85, 85, 85, 255);	

	//Initialize the Device icon 
	deviceIcon.setFixedSize(44,44);
	deviceIcon.setPixmap(QPixmap(":/DeviceWidget/iPhoneInactive.png"));

	//Initialize the Device name
	deviceName.setFont(deviceNameFont);
	deviceName.setPalette(textColorInactive);
	deviceName.setContentsMargins(10, 0, 0, 0); /*indent text from device avatar*/
	deviceName.setText("iPhone 6");

	//Add the objects to the device widget
	deviceWidgetLayout.addSpacing(5);
	deviceWidgetLayout.addWidget(&deviceIcon);
	deviceWidgetLayout.addSpacing(2);
	deviceWidgetLayout.addWidget(&deviceName);
	deviceWidgetLayout.addStretch();
	deviceWidgetLayout.addSpacing(5);
	deviceWidgetLayout.addWidget(&deviceTamperStatusIcon);
	deviceWidgetLayout.addSpacing(12);


}

void DeviceWidget::showAsInactive()
{
	this->setPalette(backgroundColorInactive);
	deviceName.setPalette(textColorInactive);
	deviceIcon.setPixmap(QPixmap(":/DeviceWidget/iPhoneInactive.png"));
}

void DeviceWidget::showAsActive()
{
	this->setPalette(backgroundColorActive);
	deviceName.setPalette(textColorActive);
	deviceIcon.setPixmap(QPixmap(":/DeviceWidget/iPhoneActive.png"));
}

void DeviceWidget::onShowTamperActivity()
{

}

void DeviceWidget::onUpdateTamperCounts()
{

}

void DeviceWidget::mouseReleaseEvent(QMouseEvent *e)
{
	emit setActiveDeviceWidget();
}

void DeviceWidget::mousePressEvent(QMouseEvent *e)
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

void DeviceWidget::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void DeviceWidget::contextMenuEvent(QContextMenuEvent *e)
{

}

void DeviceWidget::enterEvent(QEvent *e)
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

void DeviceWidget::leaveEvent(QEvent *e)
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