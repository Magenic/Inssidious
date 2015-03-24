#include "inssidious.h"

InssidiousUi::InssidiousUi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//Initialize the core of the app
	core = new Core();
	coreThread = new QThread(this);
	core->moveToThread(coreThread);

	//Initialize the header
	ui.AppLogo->setPixmap(QPixmap(":/HeaderWidget/AppLogo.png"));
	ui.WirelessNetworkNameIcon->setPixmap(QPixmap(":/HeaderWidget/WirelessNetworkNameIcon.png"));
	ui.WirelessNetworkPasswordIcon->setPixmap(QPixmap(":/HeaderWidget/WirelessNetworkPasswordIcon.png"));
	QPalette headerTextPalette;
	headerTextPalette.setColor(QPalette::WindowText, QColor("lightGray"));
	ui.WirelessNetworkNameText->setPalette(headerTextPalette);
	ui.WirelessNetworkPasswordText->setPalette(headerTextPalette);

	//Initialize Waiting For Devices Widget's layout and then hide the widget
	waitingForDevicesLayout = new QVBoxLayout();
	waitingForDevicesLayout->addSpacing(220); /* padding from the top */
	waitingForDevicesMessage = new QLabel();
	waitingForDevicesMessage->setPixmap(QPixmap(":/DeviceWidget/WaitingForDevices.png"));
	waitingForDevicesLayout->addWidget(waitingForDevicesMessage, 0, Qt::AlignLeft | Qt::AlignTop); /* align left to push image against the sidebar */
	ui.WaitingForDevicesWidget->setLayout(waitingForDevicesLayout);
	ui.WaitingForDevicesWidget->hide();

	//Initialize Critical Error Widget's layout
	criticalErrorLayout = new QVBoxLayout();
	criticalErrorLayout->addSpacing(160); /* padding from the top */

	//Initialize and add the sad error logo to the layout
	criticalErrorSadLogo = new QLabel();
	criticalErrorSadLogo->setPixmap(QPixmap(":/CriticalErrorWidget/AppSadLogo.png"));
	criticalErrorLayout->addWidget(criticalErrorSadLogo, 0, Qt::AlignCenter);
	criticalErrorLayout->addSpacing(40); /* padding from logo */

	//Initialize and add the error text to the layout
	QPalette errorOrangePalette;
	errorOrangePalette.setColor(QPalette::WindowText, QColor(255, 150, 0, 255)); /* lovely error orange */
	criticalErrorMessage = new QLabel();
	criticalErrorMessage->setPalette(errorOrangePalette);
	criticalErrorMessage->setFont(QFont("Calibri", 13)); /* bump up the font size a bit */
	criticalErrorMessage->setAlignment(Qt::AlignHCenter); /* center the text in the qlabel */
	criticalErrorLayout->addWidget(criticalErrorMessage, 0, Qt::AlignHCenter | Qt::AlignTop); /* and align it at the top & center of our padded down layout */
	criticalErrorLayout->addSpacing(40); /* padding from error message */

	//Initialize and add the quit button to the layout
	criticalErrorQuitButton = new QPushButton();
	criticalErrorQuitButton->setMinimumSize(QSize(104, 30));
	criticalErrorQuitButton->setStyleSheet("QPushButton{ border: none; background-image: url(\":/CriticalErrorWidget/QuitButtonActive.png\"); }QPushButton:hover{ background-image: url(\":/CriticalErrorWidget/QuitButtonHover.png\");}QPushButton:pressed{ background-image: url(\":/CriticalErrorWidget/QuitButtonPressed.png\");}QPushButton:focus { outline: none;}");
	criticalErrorLayout->addWidget(criticalErrorQuitButton, 0, Qt::AlignCenter);
	criticalErrorLayout->addStretch(); /* Pad the remaining layout space at the bottom to push the button up */
	connect(criticalErrorQuitButton, SIGNAL(clicked()), this, SLOT(close())); /* and connect the button clicked signal to the quit slot */

	//Hide the critical error widget until there is a critical error
	ui.CriticalErrorWidget->hide();

	//Initialize the device list sidebar widget 
	QWidget* scrollAreaWidgetContents = new QWidget();
	scrollAreaWidgetContents->setLayout(new QVBoxLayout());
	scrollAreaWidgetContents->layout()->setSpacing(5); /* five pixels between sidebar items */
	scrollAreaWidgetContents->layout()->setMargin(0);
	scrollAreaWidgetContents->setLayoutDirection(Qt::LeftToRight);
	ui.DeviceSidebarListWidgetScrollArea->setWidget(scrollAreaWidgetContents);
	ui.DeviceSidebarListWidgetScrollArea->widget()->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	//Initialize the startup widget
	startupWidget = new StartupWidget(this);

	//Add Startup Widget to the current layout and show it
	this->setLayout(new QVBoxLayout());
	this->layout()->setSpacing(0);
	this->layout()->setMargin(0);
	this->layout()->addWidget(startupWidget);
	startupWidget->show();

	//Connect initial signals and slots
	connect(coreThread, &QThread::started, core, &Core::onThreadStarted);									//Notify Core that it is on it's own thread	and that thread has started
	connect(core, &Core::coreReadyToStart, startupWidget, &StartupWidget::onCoreReadyToStart);				//Notify Startup Widget that core is ready to go
	connect(startupWidget, &StartupWidget::coreStartRouter, core, &Core::onCoreStartRouter);				//Notify Core that Startup Widget requests to start the router
	connect(core, &Core::coreRouterStarted, this, &InssidiousUi::onCoreRouterStarted);						//Notify InssidiousUi that Core has successfully started the router
	connect(core, &Core::coreFailed, this, &InssidiousUi::onCoreFailed);									//Notify InssidiousUi that core has failed 
	connect(core, &Core::coreDeviceConnected, this, &InssidiousUi::onDeviceConnected);						//Notify InssidiousUi that a device has connected
	connect(core, &Core::coreDeviceDisconnected, this, &InssidiousUi::onDeviceDisconnected);				//Notify InssidiousUi that a device has disconnected

	//Start the core thread
	coreThread->start();

	/* Core will emit a signal for StartupWidget to indicate it successfully started or failed */
}

void InssidiousUi::onCoreRouterStarted(QString networkName, QString networkPassword)
{	
	//Set the wireless network name and password
	ui.WirelessNetworkNameText->setText(networkName);
	ui.WirelessNetworkPasswordText->setText(networkPassword);

	//Hide & delete the Startup Widget
	startupWidget->hide();
	delete startupWidget;

	//Show & raise the Waiting for Devices widget
	ui.WaitingForDevicesWidget->show();
	ui.WaitingForDevicesWidget->raise();

	/* Core will emit a signal for Inssidious when a device connects to the wireless network */
}

void InssidiousUi::onCoreFailed(QString errorMessage)
{	
	//Add the errorMessage to the error text
	criticalErrorMessage->setText(errorMessage + "\n\nPlease restart Inssidious.");

	//Set the layout to the critical error layout
	ui.CriticalErrorWidget->setLayout(criticalErrorLayout);

	//Show the critical error widget and raise it to the top of the widget stack
	ui.CriticalErrorWidget->show(); 
	ui.CriticalErrorWidget->raise();

	/* No further action can be taken without restarting Inssidious */
}

void InssidiousUi::onDeviceConnected(QString MACAddress)
{
	//Create a new Device 
	Device* device = new Device(MACAddress, ui.MainAreaWidget);

	//Add the device to the list
	DeviceList.append(device);

	//Add the device widget to the sidebar
	ui.DeviceSidebarListWidgetScrollArea->widget()->layout()->addWidget(device->deviceWidget);

	//Connect the device widget clicked signal to Inssidious's on device widget clicked slot
	connect(device->deviceWidget, &DeviceWidget::deviceWidgetClicked, this, &InssidiousUi::onDeviceWidgetClicked);

	//Check if we need to hide the Waiting for Devices widget
	if (DeviceList.count() == 1) //this is the first device
	{
		//Hide the Waiting for Devices widget
		ui.WaitingForDevicesWidget->hide();

		//Tell the new Device Widget to show as active
		device->select();

	}
}

void InssidiousUi::onDeviceDisconnected(QString MACAddress)
{
	for (Device* device : DeviceList)
	{
		if (device->MACAddress == MACAddress)
		{
			//Remove the device from the list
			DeviceList.removeOne(device);

			//If this device's device widget was active, select another widget to be active instead
			if (device->isActive && DeviceList.count() != 0)
			{
				DeviceList.first()->select();
			}

			//Delete the device
			delete device;

			//If there are no other devices connected, show the Waiting for Devices widget
			if (DeviceList.count() == 0)
			{
				ui.WaitingForDevicesWidget->show();
				ui.WaitingForDevicesWidget->raise();
			}

		}
	}
}

void InssidiousUi::onDeviceWidgetClicked(DeviceWidget* deviceWidget)
{
	//For each device in the list
	for (Device* device : DeviceList)
	{
		//If it is active, set it as inactive
		if (device->isActive)
		{
			device->unselect();
		}

		//If it is the owner of the widget that signaled, set it as active 
		if (device->deviceWidget == deviceWidget)
		{
			device->select();
		}
	}
}