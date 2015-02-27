#include "inssidious.h"

Inssidious::Inssidious(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

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

	//Add it to the current layout and show it
	this->setLayout(new QVBoxLayout());
	this->layout()->setSpacing(0);
	this->layout()->setMargin(0);
	this->layout()->addWidget(startupWidget);
	startupWidget->show();

	//Start the core of the app
	core = new Core();
	coreThread = new QThread(this);
	core->moveToThread(coreThread);
	
	//Connect core's start/fail signals to StartupWidget's slots
	connect(core, &Core::coreStarted, startupWidget, &StartupWidget::onCoreStarted);
	connect(core, &Core::coreStartFailed, startupWidget, &StartupWidget::onCoreFailedToStart);
	connect(coreThread, &QThread::started, core, &Core::start);
	
	//Start the core thread
	coreThread->start();

	/* Core will emit a signal for StartupWidget to indicate it successfully started or failed */
}

Inssidious::~Inssidious()
{

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