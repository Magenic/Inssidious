#include "device.h"

Device::Device(QString m, QWidget* mainAreaWidget)
{
	//Store a copy of the MAC Address 
	MACAddress = new QString(m);

	//Initialize the Device Widget
	widget = new DeviceWidget(m);


	//Initialize the Tamper Widgets Container and container layout
	tamperWidgetsContainer = new QWidget();
	containerLayout = new QGridLayout();

	//Set the size, geometry, background color, and parent of the Tamper Widgets Container
	tamperWidgetsContainer->setFixedSize(537, 584);
	tamperWidgetsContainer->setGeometry(225, 0, 537, 584);
	tamperWidgetsContainer->setAutoFillBackground(true);
	tamperWidgetsContainer->setPalette(QColor(255, 255, 255, 255));
	tamperWidgetsContainer->setParent(mainAreaWidget);

	//Set the layout of the Tamper Widgets Container
	containerLayout->setSpacing(0);
	containerLayout->setMargin(0);
	tamperWidgetsContainer->setLayout(containerLayout);

	//Initialize the individual Tamper Widgets
	NetworkLag = new TamperWidget(NETWORK_LAG);
	DropAllTraffic = new TamperWidget(DROP_ALL_TRAFFIC);
	DropNonHttpTraffic = new TamperWidget(DROP_NON_HTTP_TRAFFIC);
	RedirectToPortal = new TamperWidget(REDIRECT_TO_PORTAL);
	WebServiceError = new TamperWidget(WEB_SERVICE_ERROR);
	WebServiceTimeOut = new TamperWidget(WEB_SERVICE_TIME_OUT);
	WebServiceEmptyResponses = new TamperWidget(WEB_SERVICE_EMPTY_RESPONSES);

	//Add the individual Tamper Widgets to the Tamper Wigets Container
	containerLayout->addWidget(NetworkLag, 0, 0);
	containerLayout->addWidget(DropAllTraffic, 1, 0);
	containerLayout->addWidget(DropNonHttpTraffic, 2, 0);
	containerLayout->addWidget(RedirectToPortal, 3, 0);
	containerLayout->addWidget(WebServiceError, 4, 0);
	containerLayout->addWidget(WebServiceTimeOut, 5, 0);
	containerLayout->addWidget(WebServiceEmptyResponses, 6, 0);

	//Connect the tamper widget's clicked signal to Inssidious' tamper widget clicked slot
	connect(NetworkLag, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(DropAllTraffic, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(DropNonHttpTraffic, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(RedirectToPortal, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(WebServiceError, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(WebServiceTimeOut, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(WebServiceEmptyResponses, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
}

Device::~Device()
{
	delete widget;
	delete tamperWidgetsContainer;
}

void Device::onTamperWidgetClicked(TamperType t)
{
	////For each device in the list
	//for (DeviceObject* deviceObject : DeviceList)
	//{
	//	//For the widget that signaled
	//	if (deviceObject->tamperWidgetsContainer == tamperWidget->parentWidget())
	//	{
	//		if (tamperWidget == deviceObject->NetworkLag)
	//		{

	//			emit en
	//		case DROP_ALL_TRAFFIC:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/2static.png"));
	//			break;
	//		case DROP_NON_HTTP_TRAFFIC:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/7static.png"));
	//			break;
	//		case REDIRECT_TO_PORTAL:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/3static.png"));
	//			break;
	//		case WEB_SERVICE_ERROR:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/4static.png"));
	//			break;
	//		case WEB_SERVICE_TIME_OUT:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/5static.png"));
	//			break;
	//		case WEB_SERVICE_EMPTY_RESPONSES:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/6static.png"));
	//			break;
	//		default:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap());
	//		}



	//		//If it is active, signal to core to deactivate the tamper option
	//		if (tamperWidget->isActive)
	//		{
	//			emit enableTamperOption();
	//		}
	//		else //Signal to core to activate the tamper option
	//		{
	//			emit disableTamperOption();
	//		}
	//	}
	//}
}

void Device::select()
{
	widget->select();
	tamperWidgetsContainer->show();
}

void Device::unselect()
{
	widget->unselect();
	tamperWidgetsContainer->hide();
}

//void Device::onTamperTypeEnabled(Device* device, Tamper* tamper)
//{
	////For each device in the list
	//for (DeviceObject* deviceObject : DeviceList)
	//{
	//	//For the device core enabled a tamper option on
	//	if (deviceObject->deviceID == deviceID)
	//	{
	//		deviceObject->activeTamperCount++;
	//		switch (tamperOption)
	//		{
	//		case NETWORK_LAG:
	//			//network lag show as active   tamperWidget->select();
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/1static.png"));
	//			break;
	//		case DROP_ALL_TRAFFIC:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/2static.png"));
	//			break;
	//		case DROP_NON_HTTP_TRAFFIC:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/7static.png"));
	//			break;
	//		case REDIRECT_TO_PORTAL:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/3static.png"));
	//			break;
	//		case WEB_SERVICE_ERROR:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/4static.png"));
	//			break;
	//		case WEB_SERVICE_TIME_OUT:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/5static.png"));
	//			break;
	//		case WEB_SERVICE_EMPTY_RESPONSES:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/6static.png"));
	//			break;
	//		default:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap());
	//		}
	//	//Add the Tamper Count Status icon
	//	}
	//}
//}

//void Device::onTamperTypeDisabled(Device* device, Tamper* tamper)
//{
	////For each device in the list
	//for (DeviceObject* deviceObject : DeviceList)
	//{
	//	//For the device core disabled a tamper option on
	//	if (deviceObject->deviceID == deviceID)
	//	{
	//		deviceObject->activeTamperCount--;
	//		switch (tamperOption)
	//		{
	//		case NETWORK_LAG:
	//			//network lag show as inactive   tamperWidget->unselect();
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/1static.png"));
	//			break;
	//		case DROP_ALL_TRAFFIC:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/2static.png"));
	//			break;
	//		case DROP_NON_HTTP_TRAFFIC:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/7static.png"));
	//			break;
	//		case REDIRECT_TO_PORTAL:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/3static.png"));
	//			break;
	//		case WEB_SERVICE_ERROR:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/4static.png"));
	//			break;
	//		case WEB_SERVICE_TIME_OUT:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/5static.png"));
	//			break;
	//		case WEB_SERVICE_EMPTY_RESPONSES:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/6static.png"));
	//			break;
	//		default:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap());
	//		}

	//		//Add the Tamper Count Status icon
	//	}
	//}
//}

//void Device::onTamperActivity(Device*)
//{
	////For each device in the list
	//for (DeviceObject* deviceObject : DeviceList)
	//{
	//	//For the device core signaled ativity on
	//	if (deviceObject->deviceID == deviceID)
	//	{
	//		switch (tamperOption)
	//		{
	//		case NETWORK_LAG:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/1active.png"));
	//			break;
	//		case DROP_ALL_TRAFFIC:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/2active.png"));
	//			break;
	//		case DROP_NON_HTTP_TRAFFIC:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/7active.png"));
	//			break;
	//		case REDIRECT_TO_PORTAL:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/3active.png"));
	//			break;
	//		case WEB_SERVICE_ERROR:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/4active.png"));
	//			break;
	//		case WEB_SERVICE_TIME_OUT:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/5active.png"));
	//			break;
	//		case WEB_SERVICE_EMPTY_RESPONSES:
	//			deviceObject->deviceWidget->deviceTamperStatusIcon.setPixmap(QPixmap(":/DeviceWidget/6active.png"));
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}
//}