/*
*  File:		inssidious.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include "InssidiousUi.h"


InssidiousUi::InssidiousUi(QWidget *parent)
	: QWidget(parent)
{

	/* Initialize default window settings */

	this->backgroundPalette.setBrush(QPalette::Background,			//Set the brush of the Background palette
		QBrush(backgroundImageLaunch));								//To use our background image
	this->setFixedSize(800, 640);									//Set an initial window size
	this->setPalette(backgroundPalette);							//Apply the background palette
	this->setWindowFlags(Qt::FramelessWindowHint);					//Remove the window frame
	this->winId();													//And force Qt to acquire the Windows window handle for the widget


	/* Draw the Minimize & Close icons */

	pushButtonClose = new QPushButton("", this);
	pushButtonMinimize = new QPushButton("", this);

	pushButtonClose->setParent(this);							
	pushButtonMinimize->setParent(this);						

	pushButtonClose->setAutoFillBackground(true);				
	pushButtonMinimize->setAutoFillBackground(true);			

	pushButtonClose->setStyleSheet(closeStyleSheet);
	pushButtonMinimize->setStyleSheet(minimizeStyleSheet);

	pushButtonClose->setIconSize(QSize(46, 31));
	pushButtonMinimize->setIconSize(QSize(46, 31));

	pushButtonClose->setGeometry(753, 1, 46, 31);
	pushButtonMinimize->setGeometry(706, 1, 46, 31);

	connect(pushButtonClose, &QPushButton::clicked, this, &InssidiousUi::close);
	connect(pushButtonMinimize, &QPushButton::clicked, this, &InssidiousUi::onMinimizeClicked);


	/* Draw and hide the network name and password labels */

	this->networkName.setParent(this);
	this->networkNameIcon.setParent(this);
	this->networkPassword.setParent(this);
	this->networkPasswordIcon.setParent(this);

	this->networkNameIcon.setGeometry(8, 8, 16, 16);
	this->networkPasswordIcon.setGeometry(8, 32, 16, 16);
	this->networkName.setGeometry(32, 8, 100, 16);
	this->networkPassword.setGeometry(32, 32, 100, 16);

	textPalette.setColor(QPalette::WindowText, QColor(51, 51, 51));
	this->networkName.setPalette(textPalette);
	this->networkPassword.setPalette(textPalette);

	this->networkName.setFont(QFont("Segoe UI", 8, QFont::Normal, false));
	this->networkPassword.setFont(QFont("Segoe UI", 8, QFont::Normal, true));

	this->networkNameIcon.setPixmap(QPixmap(":/InssidiousUi/NetworkNameIcon.png"));
	this->networkPasswordIcon.setPixmap(QPixmap(":/InssidiousUi/NetworkPasswordIcon.png"));

	this->networkName.hide();
	this->networkNameIcon.hide();
	this->networkPassword.hide();
	this->networkPasswordIcon.hide();


	/* Initialize the core backend and start the thread */

	inssidiousCore = new InssidiousCore();
	inssidiousCore->start();				


	/* Initialize and hide the tab controller for now */

	uiDeviceController = new UiDeviceController(this);
	uiDeviceController->hide();


	startWidget = new StartWidget(this, *inssidiousCore->pNetworkConnectionNames);


	/* Connect Signals and Slots */
	
	connect(startWidget, &StartWidget::uiStartCore, this, &InssidiousUi::onUiStartCore);
	connect(this, &InssidiousUi::coreStart, inssidiousCore, &InssidiousCore::onUiCoreStart, Qt::QueuedConnection);

	connect(inssidiousCore, &InssidiousCore::coreStarting, this, &InssidiousUi::onCoreStarting, Qt::QueuedConnection);
	connect(this, &InssidiousUi::uiUpdateStartingText, startWidget, &StartWidget::onUiUpdateStartingText);
	connect(inssidiousCore, &InssidiousCore::coreStarted, this, &InssidiousUi::onCoreStarted, Qt::QueuedConnection);
	connect(inssidiousCore, &InssidiousCore::coreStopped, this, &InssidiousUi::onCoreStopped, Qt::QueuedConnection);


	connect(inssidiousCore, &InssidiousCore::coreAddDevice, this, &InssidiousUi::onCoreAddDevice, Qt::QueuedConnection);
	connect(inssidiousCore, &InssidiousCore::coreDropDevice, this, &InssidiousUi::onCoreDropDevice, Qt::QueuedConnection);
	connect(this, &InssidiousUi::uiAddDevice, uiDeviceController, &UiDeviceController::onUiAddDevice);
	connect(this, &InssidiousUi::uiDropDevice, uiDeviceController, &UiDeviceController::onUiDropDevice);


	connect(uiDeviceController, &UiDeviceController::uiTamperStart, this, &InssidiousUi::onUiTamperStart);
	connect(uiDeviceController, &UiDeviceController::uiTamperStop, this, &InssidiousUi::onUiTamperStop);
	connect(this, &InssidiousUi::coreStartTamper, inssidiousCore, &InssidiousCore::onUiTamperStart, Qt::QueuedConnection);
	connect(this, &InssidiousUi::coreStopTamper, inssidiousCore, &InssidiousCore::onUiTamperStop, Qt::QueuedConnection);

	
	/* No further work until we receive signals */

}


void InssidiousUi::onUiStartCore(QString networkName, QString networkPassword, QString networkAdapter)
{
	this->networkName.setText(networkName);
	this->networkPassword.setText(networkPassword);

	emit coreStart(networkName, networkPassword, networkAdapter);
}


void InssidiousUi::onCoreStarting(QString messageText, bool isErrorMessage)
{
	emit uiUpdateStartingText(messageText, isErrorMessage);
}

void InssidiousUi::onCoreStarted()
{
	/* Hide and delete the Start Widget */

	this->startWidget->hide();
	delete this->startWidget;


	/* Change the Background and Show the Header and Tab Widgets*/

	this->backgroundPalette.setBrush(QPalette::Background,			
		QBrush(backgroundImageRunning));
	this->setPalette(backgroundPalette);
	this->uiDeviceController->show();


	/* Show the Network Name and Password in the upper left */

	this->networkName.show();
	this->networkPassword.show();
	this->networkNameIcon.show();
	this->networkPasswordIcon.show();

}


void InssidiousUi::onCoreStopped()
{
	/* TODO: Draw a nicer error screen and handle error message text */

	MessageBoxW((HWND)this->winId(), L"Inssidious stopped unexpectedly. Error: TODO", L"An error occured.", MB_OK);
	ExitProcess(1);
}

void InssidiousUi::onCoreAddDevice(QString MACAddress)
{
	emit uiAddDevice(MACAddress);
}

void InssidiousUi::onCoreDropDevice(QString MACAddress)
{
	emit uiDropDevice(MACAddress);
}

void InssidiousUi::onUiTamperStart(QString MACAddress, TamperType tamperType, void * pTamperConfig)
{
	emit coreStartTamper(MACAddress, tamperType, pTamperConfig);
}

void InssidiousUi::onUiTamperStop(QString MACAddress, TamperType tamperType)
{
	emit coreStopTamper(MACAddress, tamperType);
}


//Override the nativeEvent function to react to window messages and handle drawing & dragging
bool InssidiousUi::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	//Cast the window message to a type we can work with
	MSG *msg = static_cast<MSG *>(message);

	//Check if DWM handled the message; if it did, it wasn't in our client area and we can ignore it 
	if (DwmDefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam, (LRESULT*)result))
		return true;

	//Get the window rectangle 
	RECT winrect;
	GetWindowRect(msg->hwnd, &winrect);

	//Condition based on the message type
	switch (msg->message)
	{
		//On show window, update the frame
		case WM_SHOWWINDOW:
		{

			SetWindowPos(msg->hwnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
			return false;
		}
		//On calculate size, remove the frame
		case WM_NCCALCSIZE:
		{
			if (msg->wParam)
			{
				//Set the result to 0 to remove the window frame and caption items extending the client area into the frame
				//https://msdn.microsoft.com/en-us/library/windows/desktop/ms632634.aspx
				*result = 0;
				return 0;
			}
		}
		//Allow dragging the window
		case WM_NCHITTEST:
		{
			//Get X and Y mouse coordinate
			long y = GET_Y_LPARAM(msg->lParam);
			long x = GET_X_LPARAM(msg->lParam);

			//If the mouse is within the title bar area, allow dragging the window
			if (abs(y - winrect.top) <= 42 /* height of top area of Inssidious background */
				&& abs(x - winrect.left) < 701 /* right 99 pixels reserved for Insiddious settings, minimize and close icons */)
			{
				*result = HTCAPTION;
				return true;
			}
		}
	}

	//Pass the event on if it wasn't for us to react to
	return QWidget::nativeEvent(eventType, message, result);
}

void InssidiousUi::onMinimizeClicked()
{
	this->setWindowState(Qt::WindowMinimized);
}

void InssidiousUi::onSettingsClicked()
{
	
}





