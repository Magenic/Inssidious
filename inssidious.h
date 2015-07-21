/*
*  File:		inssidious.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:	
*				
*
*/

#ifndef INSSIDIOUS_H
#define INSSIDIOUS_H

#include "core.h"							//Inssidious creates an instance of the Core backend to drive non-UI work

#include <QtWidgets/QApplication>			//Qt GUI Application with widget support
#include <QThread>							//Qt Threading library to move Inssidious core to its own thread
#include <QtWidgets/QWidget>				//QWidgets 
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtWinExtras/QtWin>				//Qt Windows Extras for extendFrameIntoClientArea function
#include "Windowsx.h"						//Macros header for GET_X_LPARAM and GET_Y_LPARAM macros
#include "Dwmapi.h"							//DWM Api header for the DwmDefWindowProc function

#include "Widgets\header.h"					//Inssidious creates and draws the Header on the main window
#include "Widgets\tabcontroller.h"			//Inssidious creates and draws the tab controller on the main window
#include "Widgets\start.h"					//Inssidious creates and draws the Startup widget on the main window


#pragma comment(lib, "Qt5Cored.lib")		//QT Core libary
#pragma comment(lib, "Qt5Guid.lib")			//QApplication library
#pragma comment(lib, "Qt5Widgetsd.lib")		//QWidgets library
#pragma comment(lib, "Qt5WinExtras.lib")	//QtWin library
#pragma comment(lib, "dwmapi.lib")			//DWM library



class Inssidious : public QWidget
{
	Q_OBJECT

public:
	Inssidious(QWidget *parent = 0);
	~Inssidious();

public slots:
	//Receives a message from Core to trigger removing the Startup widget & showing the header and tab controller
	void onCoreStarted();					

private:
	//Override nativeEvent to react to messages sent to our window, particularly for window drawing & dragging
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;


	Core* inssidiousCore;					//Pointer to the Inssidious backend implemented in Core			

	Header* headerWidget;					//Pointer to the Header widget that controls the Menu icon and Sid logo
	TabController* tcWidget;				//Pointer to the Tabs widget that draws each device's tampering options
	Start* startupWidget;					//Pointer to the Start widget that displays on initial startup

};

#endif // INSSIDIOUS_H