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
	initialNewDeviceWidget = new QWidget();
	tamperWidgetsContainerLayout = new QGridLayout();
	initialNewDeviceLayout = new QVBoxLayout();

	//Set the size, geometry, background color, and parent of the Tamper Widgets Container
	tamperWidgetsContainer->setFixedSize(537, 584);
	tamperWidgetsContainer->setGeometry(225, 0, 537, 584);
	tamperWidgetsContainer->setAutoFillBackground(true);
	tamperWidgetsContainer->setPalette(QColor(255, 255, 255, 255));
	tamperWidgetsContainer->setParent(mainAreaWidget);
	initialNewDeviceWidget->setFixedSize(537, 584);
	initialNewDeviceWidget->setGeometry(225, 0, 537, 584);
	initialNewDeviceWidget->setAutoFillBackground(true);
	initialNewDeviceWidget->setPalette(QColor(255, 255, 255, 255));
	initialNewDeviceWidget->setParent(mainAreaWidget);

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

	//Set the tamper widget layout
	tamperWidgetsContainer->setLayout(tamperWidgetsContainerLayout);

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

		deviceHasBeenNamed = true;

		tamperWidgetsContainer->hide();
		initialNewDeviceWidget->hide();
		delete initialNewDeviceWidget;
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
		deviceNameLineEdit->setMaximumSize(160, 20);

		//Add them to the layout
		initialNewDeviceLayout->setContentsMargins(40, 60, 40, 0);
		initialNewDeviceLayout->addWidget(deviceNameTextLabel);
		initialNewDeviceLayout->addWidget(deviceNameLineEdit);
		initialNewDeviceLayout->addSpacing(10);

		//Initialize the device type icons image list
		deviceIconImageListTextLabel = new QLabel("Select a device icon: ");
		deviceIconImageList = new QListView();
		
		deviceIconImageList->setViewMode(QListView::IconMode);
		{
			iStandardModel = new QStandardItemModel(this);
			QStandardItem* item1 = new QStandardItem(QIcon(":/DeviceWidget/iPhoneActive.png"), "iPhone");
			QStandardItem* item2 = new QStandardItem(QIcon(":/DeviceWidget/AndroidActive.png"), "Android");
			QStandardItem* item3 = new QStandardItem(QIcon(":/DeviceWidget/WindowsPhoneActive.png"), "Windows Phone");
			QStandardItem* item4 = new QStandardItem(QIcon(":/DeviceWidget/iPadActive.png"), "iPad");
			QStandardItem* item5 = new QStandardItem(QIcon(":/DeviceWidget/AndroidTabletActive.png"), "Android Tablet");
			QStandardItem* item6 = new QStandardItem(QIcon(":/DeviceWidget/WindowsTabletActive.png"), "Windows Tablet");
			QStandardItem* item7 = new QStandardItem(QIcon(":/DeviceWidget/MacBookActive.png"), "MacBook");
			QStandardItem* item8 = new QStandardItem(QIcon(":/DeviceWidget/ChromebookActive.png"), "Chromebook");
			QStandardItem* item9 = new QStandardItem(QIcon(":/DeviceWidget/WindowsLaptopActive.png"), "Windows Laptop");

			iStandardModel->appendRow(item1);
			iStandardModel->appendRow(item2);
			iStandardModel->appendRow(item3);
			iStandardModel->appendRow(item4);
			iStandardModel->appendRow(item5);
			iStandardModel->appendRow(item6);
			iStandardModel->appendRow(item7);
			iStandardModel->appendRow(item8);
			iStandardModel->appendRow(item9);
			deviceIconImageList->setIconSize(QSize(48, 48));
			deviceIconImageList->setGridSize(QSize(140, 70));
			deviceIconImageList->setFrameStyle(0);
			deviceIconImageList->setUniformItemSizes(true);
			deviceIconImageList->setSelectionMode(QAbstractItemView::ExtendedSelection);
			deviceIconImageList->setDragDropMode(QAbstractItemView::DropOnly);
			deviceIconImageList->setModel(iStandardModel);
		}

		//Add them to the layout
		initialNewDeviceLayout->addWidget(deviceIconImageListTextLabel);
		initialNewDeviceLayout->addWidget(deviceIconImageList);
		initialNewDeviceLayout->addSpacing(10);

		//Draw the Set New Device Info button
		setNewDeviceInfoButton = new QPushButton();
		setNewDeviceInfoButton->setMinimumSize(QSize(104, 30));
		setNewDeviceInfoButton->setStyleSheet("QPushButton{ border: none; background-image: url(\":/DeviceWidget/SetButtonActive.png\"); }QPushButton:!enabled{background-image: url(\":/DeviceWidget/SetButtonInactive.png\");}QPushButton:hover{ background-image: url(\":/DeviceWidget/SetButtonHover.png\");}QPushButton:pressed{ background-image: url(\":/DeviceWidget/SetButtonPressed.png\");}QPushButton:focus { outline: none;}");
		initialNewDeviceLayout->addWidget(setNewDeviceInfoButton, 0, Qt::AlignCenter);

		//Pad out the bottom of the layout
		initialNewDeviceLayout->addStretch();
		
		//Connect the start button signal & slot
		connect(setNewDeviceInfoButton, SIGNAL(clicked()), this, SLOT(onSetButtonClicked()));

		//Set the layout of the tamper widgets conatiner to the initial new device layout, for now
		initialNewDeviceWidget->setLayout(initialNewDeviceLayout);

		deviceHasBeenNamed = false;	
		initialNewDeviceWidget->hide();
		tamperWidgetsContainer->hide();
	}
}

Device::~Device()
{
	delete deviceWidget;
	delete tamperWidgetsContainer;
}

void Device::onSetButtonClicked()
{
	QString deviceType = "UnknownDevice"; /* default device type if none was selected */

	for (const QModelIndex &index : deviceIconImageList->selectionModel()->selectedIndexes())
	{
		deviceType = iStandardModel->itemFromIndex(index)->text();
	}
		

	//Check whether the Device Name is of appropriate length
	if (deviceNameLineEdit->text().count() < 1 || deviceNameLineEdit->text().count() > 12) //1 - 12 is the valid length range
	{
		deviceNameTextLabel->setText("The device name must be between 1-12 characters:");
		deviceNameTextLabel->setPalette(errorTextPalette);
	}
	else
	{
		//Set the device name and type values
		this->deviceWidget->setNameAndType(deviceNameLineEdit->text(), deviceType.remove(" ")); /* remove spaces to line up device types with icon names */

		//Start the tamper threads
		NetworkLag->thread->start();
		DropAllTraffic->thread->start();
		DropNonHttpTraffic->thread->start();
		RedirectToPortal->thread->start();
		WebServiceError->thread->start();
		WebServiceTimeOut->thread->start();
		WebServiceEmptyResponses->thread->start();

		//Show the tamper widgets container and hide the new device widget
		initialNewDeviceWidget->hide();
		tamperWidgetsContainer->show();

		delete initialNewDeviceWidget;
		deviceHasBeenNamed = true;
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
	if (deviceHasBeenNamed)
	{
		tamperWidgetsContainer->show();
	}
	else
	{
		initialNewDeviceWidget->show();
	}
}

void Device::unselect()
{
	deviceWidget->unselect();
	isActive = false;
	if (deviceHasBeenNamed)
	{
		tamperWidgetsContainer->hide();
	}
	else
	{
		initialNewDeviceWidget->hide();
	}
}
