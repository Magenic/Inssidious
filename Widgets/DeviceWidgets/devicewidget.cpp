#include "devicewidget.h"

DeviceWidget::DeviceWidget(QString m)
{
	//Initialize the device name and icon text from the MAC address
	initializeNameAndIcons(m);

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
	deviceIcon.setPixmap(iconInactive);

	//Initialize the Device name
	deviceName.setFont(deviceNameFont);
	deviceName.setPalette(textColorInactive);
	deviceName.setContentsMargins(10, 0, 0, 0); /*indent text from device avatar*/
	deviceName.setText(deviceNameString);

	//Add the objects to the device widget
	deviceWidgetLayout.addSpacing(5);
	deviceWidgetLayout.addWidget(&deviceIcon);
	deviceWidgetLayout.addSpacing(2);
	deviceWidgetLayout.addWidget(&deviceName);
	deviceWidgetLayout.addStretch();
	deviceWidgetLayout.addSpacing(5);
	deviceWidgetLayout.addWidget(&tamperCount);
	deviceWidgetLayout.addSpacing(12);


}

void DeviceWidget::unselect()
{
	this->setPalette(backgroundColorInactive);
	this->deviceName.setPalette(textColorInactive);
	this->deviceIcon.setPixmap(iconInactive);
}

void DeviceWidget::select()
{
	this->setPalette(backgroundColorActive);
	this->deviceName.setPalette(textColorActive);
	this->deviceIcon.setPixmap(iconActive);
}

void DeviceWidget::setTamperCount(int totalActiveTamperCount)
{
	switch (totalActiveTamperCount)
	{
		case 0:
			this->tamperCount.setPixmap(QPixmap());
			break;
		case 1:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/1static.png"));
			break;
		case 2:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/2static.png"));
			break;
		case 3:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/3static.png"));
			break;
		case 4:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/4static.png"));
			break;
		case 5:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/5static.png"));
			break;
		case 6:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/6static.png"));
			break;
		case 7:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/7static.png"));
			break;
		default:
			this->tamperCount.setPixmap(QPixmap());
	}
}

void DeviceWidget::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background().color() == backgroundColorActivePressed)
	{
		this->setPalette(backgroundColorActive);
	}
	else if (this->palette().background().color() == backgroundColorInactivePressed)
	{
		this->setPalette(backgroundColorInactive);
	}

	emit deviceWidgetClicked(this);
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

void DeviceWidget::initializeNameAndIcons(QString m)
{
	deviceNameString = "iPhone 6";
	iconActive = QPixmap(":/DeviceWidget/iPhoneActive.png");
	iconInactive = QPixmap(":/DeviceWidget/iPhoneInactive.png");
}