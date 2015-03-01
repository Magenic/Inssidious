#include "inssidious.h"

Inssidious::Inssidious(QWidget *parent)
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

	//Initialize the device list widget sidebar
	QWidget* scrollAreaWidgetContents = new QWidget();
	scrollAreaWidgetContents->setLayout(new QVBoxLayout());
	scrollAreaWidgetContents->layout()->setSpacing(0);
	scrollAreaWidgetContents->layout()->setMargin(0);
	scrollAreaWidgetContents->setLayoutDirection(Qt::LeftToRight);
	ui.DeviceListWidgetScrollArea->setWidget(scrollAreaWidgetContents);
	ui.DeviceListWidgetScrollArea->widget()->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	//Initialize the startup widget
	startupWidget = new StartupWidget(this);

	//Add Startup Widget to the current layout and show it
	this->setLayout(new QVBoxLayout());
	this->layout()->setSpacing(0);
	this->layout()->setMargin(0);
	this->layout()->addWidget(startupWidget);
	startupWidget->show();

	//Connect initial signals and slots
	connect(core, &Core::coreStarted, startupWidget, &StartupWidget::onCoreStarted);						//Notify Startup Widget that core has successfully started
	connect(core, &Core::coreStartFailed, startupWidget, &StartupWidget::onCoreStartFailed);				//Notify Startup Widget that core has failed to start
	connect(core, &Core::inssidiousStartFailed, startupWidget, &StartupWidget::onInssidiousStartFailed);	//Notify Startup Widget that core has failed to start Inssidious
	connect(coreThread, &QThread::started, core, &Core::onThreadStart);										//Notify Core that it is on it's own thread	and that thread has started
	connect(startupWidget, &StartupWidget::inssidiousStart, core, &Core::onInssidiousStart);				//Notify Core that Startup Widget requests to start Inssidious 
	connect(core, &Core::inssidiousStarted, this, &Inssidious::onInssidiousStarted);						//Notify Inssidious (main) that Core has successfully started Inssidious
	
	//Start the core thread
	coreThread->start();

	/* Core will emit a signal for StartupWidget to indicate it successfully started or failed */
}

Inssidious::~Inssidious()
{

}

void Inssidious::onInssidiousStarted(/* wireless network name and password */)
{	
	//Set the wireless network name and password
	ui.WirelessNetworkNameText->setText("Inssidious - Ian");
	ui.WirelessNetworkPasswordText->setText("inssidious");

	//Hide the Startup Widget
	startupWidget->hide();

	//Add waiting for devices image
	QVBoxLayout* tamperAreaWidgetLayout = new QVBoxLayout();
	tamperAreaWidgetLayout->addSpacing(200); /* padding from the top */
	QLabel* waitingForDevicesMessage = new QLabel();
	waitingForDevicesMessage->setPixmap(QPixmap(":/DeviceWidget/WaitingForDevices.png"));
	tamperAreaWidgetLayout->addWidget(waitingForDevicesMessage, 0, Qt::AlignLeft | Qt::AlignTop);
	ui.TamperAreaWidget->setLayout(tamperAreaWidgetLayout);
}

void Inssidious::showDeviceWidget()
{

}

void Inssidious::deviceConnected()
{

}

void Inssidious::deviceDisconnected()
{

}