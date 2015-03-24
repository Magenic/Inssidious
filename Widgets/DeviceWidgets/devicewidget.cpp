#include "devicewidget.h"

DeviceWidget::DeviceWidget()
{
	//Set initial device name and icon QPixmaps 
	deviceName.setText("New Device Joined");
	iconActive = QPixmap(":/DeviceWidget/NewDeviceActive.png");
	iconInactive = QPixmap(":/DeviceWidget/NewDeviceInactive.png");

	//Enable mouse tracking for hover highlighting on the sidebar
	this->setMouseTracking(true);

	//Set the device widget background to a dark grey
	this->setAutoFillBackground(true);
	this->setPalette(QPalette(QPalette::Background, QColor(65, 65, 65, 255)));

	//Set the device widget size
	this->setFixedWidth(210);
	this->setFixedHeight(56);

	//Zero the layout spacing & margin and set layout for the device widget
	deviceWidgetLayout.setSpacing(0);
	deviceWidgetLayout.setMargin(0);
	this->setLayout(&deviceWidgetLayout);

	//Initialize the Device Name font
	deviceNameFont.setPointSize(18);
	deviceNameFont.setFamily("Segoe UI Semibold");
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
	deviceIcon.setFixedSize(48,48);
	deviceIcon.setPixmap(iconInactive);

	//Initialize the Device name
	deviceName.setFont(deviceNameFont);
	deviceName.setPalette(textColorInactive);
	deviceName.setContentsMargins(10, 0, 0, 0); /*indent text from device avatar*/

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
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/1.png"));
			break;
		case 2:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/2.png"));
			break;
		case 3:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/3.png"));
			break;
		case 4:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/4.png"));
			break;
		case 5:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/5.png"));
			break;
		case 6:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/6.png"));
			break;
		case 7:
			this->tamperCount.setPixmap(QPixmap(":/DeviceWidget/7.png"));
			break;
		default:
			this->tamperCount.setPixmap(QPixmap());
	}
}

void DeviceWidget::setNameAndType(QString name, QString type)
{
	//Set the device name
	this->deviceName.setText(name);

	//Set the appropriate QPixmap values
	this->iconActive = QPixmap(":/DeviceWidget/" + type + "Active.png");
	this->iconInactive = QPixmap(":/DeviceWidget/" + type + "Inactive.png");

	//Update name and pixmap
	this->select();
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

