#include "device.h"

Device::Device(QString m, QWidget* mainAreaWidget)
{
	//Store a copy of the MAC Address 
	MACAddress = new QString(m);

	//Initialize the Device Widget
	deviceWidget = new DeviceWidget();

	//Move the tamper functions to their own threads
	NetworkLag->tamper->moveToThread(NetworkLag->thread);
	DropAllTraffic->tamper->moveToThread(DropAllTraffic->thread);
	DropNonHttpTraffic->tamper->moveToThread(DropNonHttpTraffic->thread);
	RedirectToPortal->tamper->moveToThread(RedirectToPortal->thread);
	WebServiceError->tamper->moveToThread(WebServiceError->thread);
	WebServiceTimeOut->tamper->moveToThread(WebServiceTimeOut->thread);
	WebServiceEmptyResponses->tamper->moveToThread(WebServiceEmptyResponses->thread);

	//Initialize the Tamper Widgets Container and layouts
	tamperWidgetsContainer = new QWidget();
	tamperWidgetsContainerLayout = new QGridLayout();
	initialNewDeviceLayout = new QGridLayout();

	//Set the size, geometry, background color, and parent of the Tamper Widgets Container
	tamperWidgetsContainer->setFixedSize(537, 584);
	tamperWidgetsContainer->setGeometry(225, 0, 537, 584);
	tamperWidgetsContainer->setAutoFillBackground(true);
	tamperWidgetsContainer->setPalette(QColor(255, 255, 255, 255));
	tamperWidgetsContainer->setParent(mainAreaWidget);

	//Set the spacing and margin of the Tamper Widgets Container layout and add the individual tamper widgets
	tamperWidgetsContainerLayout->setSpacing(0);
	tamperWidgetsContainerLayout->setMargin(0);
	tamperWidgetsContainerLayout->addWidget(NetworkLag->widget, 0, 0);
	tamperWidgetsContainerLayout->addWidget(DropAllTraffic->widget, 1, 0);
	tamperWidgetsContainerLayout->addWidget(DropNonHttpTraffic->widget, 2, 0);
	tamperWidgetsContainerLayout->addWidget(RedirectToPortal->widget, 3, 0);
	tamperWidgetsContainerLayout->addWidget(WebServiceError->widget, 4, 0);
	tamperWidgetsContainerLayout->addWidget(WebServiceTimeOut->widget, 5, 0);
	tamperWidgetsContainerLayout->addWidget(WebServiceEmptyResponses->widget, 6, 0);

	//Connect the tamper widget's clicked signal to Inssidious' tamper widget clicked slot
	connect(NetworkLag->widget, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(DropAllTraffic->widget, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(DropNonHttpTraffic->widget, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(RedirectToPortal->widget, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(WebServiceError->widget, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(WebServiceTimeOut->widget, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);
	connect(WebServiceEmptyResponses->widget, &TamperWidget::tamperWidgetClicked, this, &Device::onTamperWidgetClicked);

	//Connect the tamper functions' activity signal to Tamper Widget's on tamper activity slot
	connect((TamperNetworkLag*)NetworkLag->tamper, &TamperNetworkLag::activity, NetworkLag->widget, &TamperWidget::onTamperActivity);
	connect((TamperNetworkLag*)DropAllTraffic->tamper, &TamperNetworkLag::activity, DropAllTraffic->widget, &TamperWidget::onTamperActivity);
	connect((TamperNetworkLag*)DropNonHttpTraffic->tamper, &TamperNetworkLag::activity, DropNonHttpTraffic->widget, &TamperWidget::onTamperActivity);
	connect((TamperNetworkLag*)RedirectToPortal->tamper, &TamperNetworkLag::activity, RedirectToPortal->widget, &TamperWidget::onTamperActivity);
	connect((TamperNetworkLag*)WebServiceError->tamper, &TamperNetworkLag::activity, WebServiceError->widget, &TamperWidget::onTamperActivity);
	connect((TamperNetworkLag*)WebServiceTimeOut->tamper, &TamperNetworkLag::activity, WebServiceTimeOut->widget, &TamperWidget::onTamperActivity);
	connect((TamperNetworkLag*)WebServiceEmptyResponses->tamper, &TamperNetworkLag::activity, WebServiceEmptyResponses->widget, &TamperWidget::onTamperActivity);

	//Set that we're not active until someone says otherwise
	isActive = false;


	//If we know what this MAC address should be named & device typed as, skip the new device layout
	if (false)
	{
		//deviceWidget->setNameAndType();
		tamperWidgetsContainer->setLayout(tamperWidgetsContainerLayout);
	}
	else
	{
		//Set the description text palette to a light grey 
		descriptionTextPalette.setColor(QPalette::WindowText, QColor("lightGray"));

		//Set the error text palette to red 
		errorTextPalette.setColor(QPalette::WindowText, QColor(255, 150, 0, 255));

		//Set the device name text label and initialize the line edit
		deviceNameTextLabel = new QLabel("Specify the name of the device:");		
		deviceNameLineEdit = new QLineEdit();

		//Add them to the layout
		initialNewDeviceLayout->addWidget(deviceNameTextLabel);
		initialNewDeviceLayout->addWidget(deviceNameLineEdit);

		//Initialize the device type icons image list
		deviceIconImageList = new QListView();
		deviceIconImageList->setViewMode(QListView::IconMode);
		deviceIconImageList->setGridSize(QSize(104, 104));

		

		//Draw the Set New Device Info button
		setNewDeviceInfoButton = new QPushButton();
		setNewDeviceInfoButton->setMinimumSize(QSize(104, 30));
		setNewDeviceInfoButton->setStyleSheet("QPushButton{ border: none; background-image: url(\":/DeviceWidget/SetButtonActive.png\"); }QPushButton:!enabled{background-image: url(\":/DeviceWidget/SetButtonInactive.png\");}QPushButton:hover{ background-image: url(\":/DeviceWidget/SetButtonHover.png\");}QPushButton:pressed{ background-image: url(\":/DeviceWidget/SetButtonPressed.png\");}QPushButton:focus { outline: none;}");
		initialNewDeviceLayout->addWidget(setNewDeviceInfoButton, 0, Qt::AlignCenter);

		//Connect the start button signal & slot
		connect(setNewDeviceInfoButton, SIGNAL(clicked()), this, SLOT(onSetButtonClicked()));

		//Set the layout of the tamper widgets conatiner to the initial new device layout, for now
		tamperWidgetsContainer->setLayout(initialNewDeviceLayout);
	}

}

Device::~Device()
{
	delete deviceWidget;
	delete tamperWidgetsContainer;
}

void Device::onSetButtonClicked()
{

	//Valid device name length 

	if (true)
	{
		//Set the device name and type values
		//this->deviceWidget->setNameAndType();

		//Start the tamper threads
		NetworkLag->thread->start();
		DropAllTraffic->thread->start();
		DropNonHttpTraffic->thread->start();
		RedirectToPortal->thread->start();
		WebServiceError->thread->start();
		WebServiceTimeOut->thread->start();
		WebServiceEmptyResponses->thread->start();

		//Change the tamper widgets container to use the tamper widgets container layout 
		tamperWidgetsContainer->setLayout(tamperWidgetsContainerLayout);
		
	}
}

void Device::onTamperWidgetClicked(TamperType t)
{
	//For the widget that signaled
	switch (t)
	{
		case NETWORK_LAG:
			if (NetworkLag->isActive)
			{
				NetworkLag->isActive = false;
				NetworkLag->tamper->isActive = false;
				NetworkLag->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				NetworkLag->isActive = true;
				NetworkLag->tamper->start();
				NetworkLag->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case DROP_ALL_TRAFFIC:
			if (DropAllTraffic->isActive)
			{
				DropAllTraffic->isActive = false;
				DropAllTraffic->tamper->isActive = false;
				DropAllTraffic->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				DropAllTraffic->isActive = true;
				DropAllTraffic->tamper->start();
				DropAllTraffic->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case DROP_NON_HTTP_TRAFFIC:
			if (DropNonHttpTraffic->isActive)
			{
				DropNonHttpTraffic->isActive = false;
				DropNonHttpTraffic->tamper->isActive = false;
				DropNonHttpTraffic->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				DropNonHttpTraffic->isActive = true;
				DropNonHttpTraffic->tamper->start();
				DropNonHttpTraffic->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case REDIRECT_TO_PORTAL:
			if (RedirectToPortal->isActive)
			{
				RedirectToPortal->isActive = false;
				RedirectToPortal->tamper->isActive = false;
				RedirectToPortal->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				RedirectToPortal->isActive = true;
				RedirectToPortal->tamper->start();
				RedirectToPortal->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case WEB_SERVICE_ERROR:
			if (WebServiceError->isActive)
			{
				WebServiceError->isActive = false;
				WebServiceError->tamper->isActive = false;
				WebServiceError->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				WebServiceError->isActive = true;
				WebServiceError->tamper->start();
				WebServiceError->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case WEB_SERVICE_TIME_OUT:
			if (WebServiceTimeOut->isActive)
			{
				WebServiceTimeOut->isActive = false;
				WebServiceTimeOut->tamper->isActive = false;
				WebServiceTimeOut->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				WebServiceTimeOut->isActive = true;
				WebServiceTimeOut->tamper->start();
				WebServiceTimeOut->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case WEB_SERVICE_EMPTY_RESPONSES:
			if (WebServiceEmptyResponses->isActive)
			{
				WebServiceEmptyResponses->isActive = false;
				WebServiceEmptyResponses->tamper->isActive = false;
				WebServiceEmptyResponses->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				WebServiceEmptyResponses->isActive = true;
				WebServiceEmptyResponses->tamper->start();
				WebServiceEmptyResponses->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		default:
			break;
	}
}

void Device::select()
{
	deviceWidget->select();
	isActive = true;
	tamperWidgetsContainer->show();
}

void Device::unselect()
{
	deviceWidget->unselect();
	isActive = false;
	tamperWidgetsContainer->hide();
}
