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
		QBrush(backgroundImage));									//To use our background image
	this->setFixedSize(800, 600);									//Set an initial window size
	this->setPalette(backgroundPalette);							//Apply the background palette
	this->setWindowFlags(Qt::FramelessWindowHint);					//Remove the window frame
	this->winId();													//And force Qt to acquire the Windows window handle for the widget


	/* Initialize the core backend and start the thread */

	inssidiousCore = new InssidiousCore();
	inssidiousCore->start();				


	/* Initialize the Ui objects and hide the header and tab sidebar for now */

	headerWidget = new HeaderWidget(this);	
	headerWidget->hide();
	tabController = new TabController(this);
	tabController->hide();
	startWidget = new StartWidget(this,	*inssidiousCore->pNetworkConnectionNames);


	/* Connect Signals and Slots */
	
	connect(startWidget, &StartWidget::uiStartCore, this, &InssidiousUi::onUiStartCore);
	connect(this, &InssidiousUi::coreStart, inssidiousCore, &InssidiousCore::onUiCoreStart, Qt::QueuedConnection);

	connect(inssidiousCore, &InssidiousCore::coreStarting, this, &InssidiousUi::onCoreStarting, Qt::QueuedConnection);
	connect(this, &InssidiousUi::uiUpdateStartingText, startWidget, &StartWidget::onUiUpdateStartingText);
	connect(inssidiousCore, &InssidiousCore::coreStarted, this, &InssidiousUi::onCoreStarted, Qt::QueuedConnection);
	connect(inssidiousCore, &InssidiousCore::coreStopped, this, &InssidiousUi::onCoreStopped, Qt::QueuedConnection);


	connect(inssidiousCore, &InssidiousCore::coreAddDevice, this, &InssidiousUi::onCoreAddDevice, Qt::QueuedConnection);
	connect(inssidiousCore, &InssidiousCore::coreDropDevice, this, &InssidiousUi::onCoreDropDevice, Qt::QueuedConnection);
	connect(this, &InssidiousUi::uiAddDevice, tabController, &TabController::onUiAddDevice);
	connect(this, &InssidiousUi::uiDropDevice, tabController, &TabController::onUiDropDevice);


	connect(tabController, &TabController::uiTamperStart, this, &InssidiousUi::onUiTamperStart);
	connect(tabController, &TabController::uiTamperStop, this, &InssidiousUi::onUiTamperStop);
	connect(this, &InssidiousUi::coreStartTamper, inssidiousCore, &InssidiousCore::onUiCoreStartTamper, Qt::QueuedConnection);
	connect(this, &InssidiousUi::coreStopTamper, inssidiousCore, &InssidiousCore::onUiCoreStopTamper, Qt::QueuedConnection);
	connect(inssidiousCore, &InssidiousCore::coreTamperStarted, this, &InssidiousUi::onCoreTamperStarted, Qt::QueuedConnection);
	connect(inssidiousCore, &InssidiousCore::coreTamperStopped, this, &InssidiousUi::onCoreTamperStopped, Qt::QueuedConnection);



	/* No further work until we receive signals */

}


void InssidiousUi::onUiStartCore(QString networkName, QString networkPassword, QString networkAdapter)
{
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


	/* Show the Header and Tab Widgets*/

	this->headerWidget->show();
	this->tabController->show();
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

void InssidiousUi::onUiTamperStart(QString MACAddress, TamperType tamperType)
{
	emit coreStartTamper(MACAddress, tamperType);
}

void InssidiousUi::onUiTamperStop(QString MACAddress, TamperType tamperType)
{
	emit coreStopTamper(MACAddress, tamperType);
}

void InssidiousUi::onCoreTamperStarted(QString MACAddress, TamperType tamperType)
{
	emit uiTamperStarted(MACAddress, tamperType);
}

void InssidiousUi::onCoreTamperStopped(QString MACAddress, TamperType tamperType)
{
	emit uiTamperStopped(MACAddress, tamperType);
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
			if (abs(y - winrect.top) <= GetSystemMetrics(SM_CYCAPTION) /* SM_CYCAPTION is title bar height */
				&& abs(x - winrect.left) > 100 /* first 100 pixels reserved for Insiddious menu */)
			{
				*result = HTCAPTION;
				return true;
			}
		}
	}

	//Pass the event on if it wasn't for us to react to
	return QWidget::nativeEvent(eventType, message, result);
}