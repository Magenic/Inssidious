/*
*  File:		inssidious.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:	
*				
*
*/


#include "inssidious.h"


Inssidious::Inssidious(QWidget *parent)
	: QWidget(parent)
{

	/* Initialize default window settings */

	this->setFixedSize(800, 600);									//Sets an initial window size	
	this->setAttribute(Qt::WA_TranslucentBackground);				//Removes the default tan system background from the window
	this->winId();													//Forces Qt to acquire the Windows window handle for the widget
	QtWin::extendFrameIntoClientArea(this->windowHandle(),			//Extends the Windows system frame into the widget drawing area
									 -1, -1, -1, -1);				//-1 instructs to eat all available space

	
	/* Initialize the Inssidious backend */

	inssidiousCore = new Core();									//Creates the Core instance as a unique thread
	inssidiousCore->start();										//Starts the thread, Core populates list of network adapters


	/* Initialize the Header and Tabs widgets, hide them for now */
	
	headerWidget = new Header(this);								//Draw the Header widget
	tabsWidget = new Tabs(this);									//Draw the Tabs widget
	headerWidget->hide();											//Hide it for now until we hear from Core
	//tabsWidget->hide();												//Hide it for now until we hear from Core
	tabsWidget->addTab();
	tabsWidget->addTab();
	tabsWidget->addTab();
	tabsWidget->addTab();
	tabsWidget->addTab();


	/* Initialize the Startup widget and connect a few signals */
	
	startupWidget = new Start(this,									//Draw the initial Inssidious Startup Widget on the window
		*inssidiousCore->pNetworkConnectionNames);					//Passing along the list of network adapter descriptions
	connect(startupWidget, &Start::startCore,						//Connect the startInssidious signal from startupWidget
			inssidiousCore, &Core::onCoreStart);					//to the onCoreStart slot in the Core class
	connect(inssidiousCore, &Core::updateStatus,					//Connect the updateStatus signal from Core
			startupWidget, &Start::onUpdateStatus);					//to the onUpdateStatus slot in the Start class
	connect(inssidiousCore, &Core::started,							//Connect the updateStatus signal from Core
		this, &Inssidious::onCoreStarted);							//to the onUpdateStatus slot in the Start class


	/* Startup Widget will emit a signal to direct further activity */


	startupWidget->hide();
}


//
Inssidious::~Inssidious()
{

}


//
void Inssidious::onCoreStarted()
{

	/* Hide Startup Widget, show the Header and Tabs widgets */

	this->headerWidget->show();
	this->tabsWidget->show();
	this->startupWidget->hide();

}


//Override nativeEvent to react to messages sent to our window, particularly for window drawing & dragging
bool Inssidious::nativeEvent(const QByteArray& eventType, void* message, long* result)
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
			SetWindowPos(
				msg->hwnd,
				NULL,
				winrect.left,
				winrect.top,
				winrect.right - winrect.left,
				winrect.bottom - winrect.top,
				SWP_FRAMECHANGED
				);
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

				//Return true to indicate we've acted on this event
				return true;
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