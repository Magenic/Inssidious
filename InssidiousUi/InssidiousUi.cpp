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

	this->backgroundPalette.setBrush(QPalette::Background,			//
		QBrush(backgroundImage));									//
	this->setFixedSize(800, 600);									//Sets an initial window size
	this->setPalette(backgroundPalette);							//Sets the background palette
	this->setWindowFlags(Qt::FramelessWindowHint);					//Removes the window frame
	this->winId();													//Forces Qt to acquire the Windows window handle for the widget


	/* Initialize the Inssidious backend */

	inssidiousCore = new InssidiousCore();									//Creates the Core instance as a unique thread
	inssidiousCore->start();										//Starts the thread, Core populates list of network adapters


	/* Initialize the Header and Tabs widgets, hide them for now */

	headerWidget = new HeaderWidget(this);							//Draw the Header widget
	tabController = new TabController(this);						//Draw the Tabs widget
	headerWidget->hide();											//Hide it for now until we hear from Core
	tabController->hide();												//Hide it for now until we hear from Core


	/* Initialize the Startup widget and connect signals to slots */

	startupWidget = new StartWidget(this,									//Draw the initial Inssidious Startup Widget on the window
		*inssidiousCore->pNetworkConnectionNames);					//Passing along the list of network adapter descriptions
	connect(startupWidget, &StartWidget::startCore,						//Connect the startInssidious signal from startupWidget
		inssidiousCore, &InssidiousCore::onCoreStart);					//to the onCoreStart slot in the Core class
	connect(inssidiousCore, &InssidiousCore::updateStatus,					//Connect the updateStatus signal from Core
		startupWidget, &StartWidget::onUpdateStatus);					//to the onUpdateStatus slot in the Start class
	connect(inssidiousCore, &InssidiousCore::started,							//Connect the updateStatus signal from Core
		this, &InssidiousUi::onCoreStarted);							//to the onUpdateStatus slot in the Start class
	connect(inssidiousCore, &InssidiousCore::deviceConnected,					//Connect the deviceConnected signal from Core
		tabController, &TabController::onDeviceConnected);				//to the onDeviceConnected slot in the Tab Controller class
	connect(inssidiousCore, &InssidiousCore::deviceDisconnected,				//Connect the deviceDisconnected signal from Core
		tabController, &TabController::onDeviceDisconnected);			//to the onDeviceDisconnected slot in the Tab Controller class


	/* Startup Widget will emit a signal to direct further activity */

}


//
InssidiousUi::~InssidiousUi()
{

}


//Receives a message from Core to trigger removing the Startup widget & showing the header and tab controller
void InssidiousUi::onCoreStarted()
{

	/* Hide Startup Widget, show the Header and Tabs widgets */

	this->startupWidget->hide();
	this->headerWidget->show();
	this->tabController->show();

}


//Override nativeEvent to react to messages sent to our window, particularly for window drawing & dragging
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