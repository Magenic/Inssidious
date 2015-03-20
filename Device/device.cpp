#include "device.h"

Device::Device(QString m, QWidget* mainAreaWidget)
{
	//Store a copy of the MAC Address 
	MACAddress = new QString(m);

	//Initialize the Device Widget
	deviceWidget = new DeviceWidget(m);

	//Move the tamper functions to their own threads
	NetworkLag->tamper->moveToThread(NetworkLag->thread);
	DropAllTraffic->tamper->moveToThread(DropAllTraffic->thread);
	DropNonHttpTraffic->tamper->moveToThread(DropNonHttpTraffic->thread);
	RedirectToPortal->tamper->moveToThread(RedirectToPortal->thread);
	WebServiceError->tamper->moveToThread(WebServiceError->thread);
	WebServiceTimeOut->tamper->moveToThread(WebServiceTimeOut->thread);
	WebServiceEmptyResponses->tamper->moveToThread(WebServiceEmptyResponses->thread);

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

	//Add the individual Tamper Widgets to the Tamper Wigets Container
	containerLayout->addWidget(NetworkLag->widget, 0, 0);
	containerLayout->addWidget(DropAllTraffic->widget, 1, 0);
	containerLayout->addWidget(DropNonHttpTraffic->widget, 2, 0);
	containerLayout->addWidget(RedirectToPortal->widget, 3, 0);
	containerLayout->addWidget(WebServiceError->widget, 4, 0);
	containerLayout->addWidget(WebServiceTimeOut->widget, 5, 0);
	containerLayout->addWidget(WebServiceEmptyResponses->widget, 6, 0);

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

	//Start the threads
	NetworkLag->thread->start();
	DropAllTraffic->thread->start();
	DropNonHttpTraffic->thread->start();
	RedirectToPortal->thread->start();
	WebServiceError->thread->start();
	WebServiceTimeOut->thread->start();
	WebServiceEmptyResponses->thread->start();
}

Device::~Device()
{
	delete deviceWidget;
	delete tamperWidgetsContainer;
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
				NetworkLag->tamper->stop();
				NetworkLag->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				NetworkLag->isActive = true;
				NetworkLag->tamper->tamper();
				NetworkLag->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case DROP_ALL_TRAFFIC:
			if (DropAllTraffic->isActive)
			{
				DropAllTraffic->isActive = false;
				DropAllTraffic->tamper->stop();
				DropAllTraffic->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				DropAllTraffic->isActive = true;
				DropAllTraffic->tamper->tamper();
				DropAllTraffic->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case DROP_NON_HTTP_TRAFFIC:
			if (DropNonHttpTraffic->isActive)
			{
				DropNonHttpTraffic->isActive = false;
				DropNonHttpTraffic->tamper->stop();
				DropNonHttpTraffic->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				DropNonHttpTraffic->isActive = true;
				DropNonHttpTraffic->tamper->tamper();
				DropNonHttpTraffic->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case REDIRECT_TO_PORTAL:
			if (RedirectToPortal->isActive)
			{
				RedirectToPortal->isActive = false;
				RedirectToPortal->tamper->stop();
				RedirectToPortal->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				RedirectToPortal->isActive = true;
				RedirectToPortal->tamper->tamper();
				RedirectToPortal->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case WEB_SERVICE_ERROR:
			if (WebServiceError->isActive)
			{
				WebServiceError->isActive = false;
				WebServiceError->tamper->stop();
				WebServiceError->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				WebServiceError->isActive = true;
				WebServiceError->tamper->tamper();
				WebServiceError->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case WEB_SERVICE_TIME_OUT:
			if (WebServiceTimeOut->isActive)
			{
				WebServiceTimeOut->isActive = false;
				WebServiceTimeOut->tamper->stop();
				WebServiceTimeOut->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				WebServiceTimeOut->isActive = true;
				WebServiceTimeOut->tamper->tamper();
				WebServiceTimeOut->widget->select();
				deviceWidget->setTamperCount(++totalActiveTamperCount);
			}
			break;
		case WEB_SERVICE_EMPTY_RESPONSES:
			if (WebServiceEmptyResponses->isActive)
			{
				WebServiceEmptyResponses->isActive = false;
				WebServiceEmptyResponses->tamper->stop();
				WebServiceEmptyResponses->widget->unselect();
				deviceWidget->setTamperCount(--totalActiveTamperCount);
			}
			else
			{
				WebServiceEmptyResponses->isActive = true;
				WebServiceEmptyResponses->tamper->tamper();
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
	tamperWidgetsContainer->show();
}

void Device::unselect()
{
	deviceWidget->unselect();
	tamperWidgetsContainer->hide();
}
