#include "deviceobject.h"

DeviceObject::DeviceObject(QWidget* scrollAreaWidget, QWidget* mainAreaWidget)
{
	deviceType = DeviceWidget::DeviceType{ "iPhone 6", QPixmap(":/DeviceWidget/iPhoneActive.png"), QPixmap(":/DeviceWidget/iPhoneInactive.png"), 0 };

	deviceWidget = new DeviceWidget(deviceType);
	tamperWidgetsContainer = new QWidget();

	//Add the Device Widget to the side bar
	scrollAreaWidget->layout()->addWidget(deviceWidget);

	//Connect the device widget set active signal to Device Object's set active slot
	connect(deviceWidget, &DeviceWidget::setActiveDeviceWidget, this, &DeviceObject::onSetActiveDeviceWidget);

	//Add the Tamper Widgets Container as a child of the Main Area widget
	tamperWidgetsContainer->setParent(mainAreaWidget);

	//Set the size, geometry, and background color of the Tamper Widgets Container
	tamperWidgetsContainer->setFixedSize(537, 584);
	tamperWidgetsContainer->setGeometry(225, 0, 537, 584);
	tamperWidgetsContainer->setAutoFillBackground(true);
	tamperWidgetsContainer->setPalette(QColor(255, 255, 255, 255));

	//Set the layout of the Tamper Widgets Container
	tamperWidgetsContainerLayout.setSpacing(0);
	tamperWidgetsContainerLayout.setMargin(0);
	tamperWidgetsContainer->setLayout(&tamperWidgetsContainerLayout);

	//Initialize the individual Tamper Widgets
	TamperWidget* NetworkLag = new TamperWidget(NETWORK_LAG);
	TamperWidget* DropAllTraffic = new TamperWidget(DROP_ALL_TRAFFIC);
	TamperWidget* DropNonHttpTraffic = new TamperWidget(DROP_NON_HTTP_TRAFFIC);
	TamperWidget* RedirectToPortal = new TamperWidget(REDIRECT_TO_PORTAL);
	TamperWidget* WebServiceError = new TamperWidget(WEB_SERVICE_ERROR);
	TamperWidget* WebServiceTimeOut = new TamperWidget(WEB_SERVICE_TIME_OUT);
	TamperWidget* WebServiceEmptyResponses = new TamperWidget(WEB_SERVICE_EMPTY_RESPONSES);

	//Add the individual Tamper Widgets to the Tamper Wigets Container
	tamperWidgetsContainerLayout.addWidget(NetworkLag, 0, 0);
	tamperWidgetsContainerLayout.addWidget(DropAllTraffic, 1, 0);
	tamperWidgetsContainerLayout.addWidget(DropNonHttpTraffic, 2, 0);
	tamperWidgetsContainerLayout.addWidget(RedirectToPortal, 3, 0);
	tamperWidgetsContainerLayout.addWidget(WebServiceError, 4, 0);
	tamperWidgetsContainerLayout.addWidget(WebServiceTimeOut, 5, 0);
	tamperWidgetsContainerLayout.addWidget(WebServiceEmptyResponses, 6, 0);


}

DeviceObject::~DeviceObject()
{
	delete deviceWidget;
	/* each tamper widget */
	delete tamperWidgetsContainer;
}

bool DeviceObject::isActive()
{
	return isActiveDeviceWidget;
}

void DeviceObject::setActive()
{
	deviceWidget->showAsActive();
	tamperWidgetsContainer->show();
	isActiveDeviceWidget = true;
}

void DeviceObject::setInactive()
{
	deviceWidget->showAsInactive();
	tamperWidgetsContainer->hide();
	isActiveDeviceWidget = false;
}

void DeviceObject::onSetActiveDeviceWidget()
{
	emit switchDeviceWidgets(this);
}