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

	//Initialize Tamper Area's No Devices layout
	tamperAreaNoDevicesLayout = new QVBoxLayout();
	tamperAreaNoDevicesLayout->addSpacing(220); /* padding from the top */
	noDevicesMessage = new QLabel();
	noDevicesMessage->setPixmap(QPixmap(":/DeviceWidget/WaitingForDevices.png"));
	tamperAreaNoDevicesLayout->addWidget(noDevicesMessage, 0, Qt::AlignLeft | Qt::AlignTop); /* align left to push image against the sidebar */

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
	scrollAreaWidgetContents->layout()->setSpacing(0);
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
	connect(core, &Core::coreThreadReady, startupWidget, &StartupWidget::onCoreThreadReady);				//Notify Startup Widget that core is ready to go
	connect(startupWidget, &StartupWidget::coreStartInssidious, core, &Core::onCoreStartInssidious);		//Notify Core that Startup Widget requests to start Inssidious 

	connect(core, &Core::inssidiousStarted, this, &Inssidious::onInssidiousStarted);						//Notify Inssidious (main) that Core has successfully started Inssidious
	connect(core, &Core::inssidiousCriticalError, this, &Inssidious::onInssidiousCriticalError);			//Notify Startup Widget that core has failed to start Inssidious

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

	//Set the layout to the No Devices layout
	ui.TamperAreaWidget->setLayout(tamperAreaNoDevicesLayout);
}

void Inssidious::onInssidiousCriticalError(QString errorMessage)
{	
	//Add the errorMessage to the error text
	criticalErrorMessage->setText(errorMessage + "\nPlease restart Inssidious.");

	//Set the layout to the critical error layout
	ui.CriticalErrorWidget->setLayout(criticalErrorLayout);

	//Show the critical error widget and raise it to the top of the widget stack
	ui.CriticalErrorWidget->show(); 
	ui.CriticalErrorWidget->raise();

	/* No further action can be taken without restarting Inssidious */
}

void Inssidious::onShowDeviceWidget()
{

}

void Inssidious::onDeviceConnected()
{

}

void Inssidious::onDeviceDisconnected()
{
	if (false)
	{
		//If there are no other devices connected, set the Main Area layout to the No Devices layout
		ui.TamperAreaWidget->setLayout(tamperAreaNoDevicesLayout);
	}
}