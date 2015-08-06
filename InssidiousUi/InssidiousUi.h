/*
*  File:		inssidious.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/

#ifndef INSSIDIOUSUI_H
#define INSSIDIOUSUI_H

#include <InssidiousCore/InssidiousCore.h>	//Inssidious creates an instance of the Core backend to drive non-UI work

#include <QtWidgets/QApplication>			//Qt GUI Application with widget support
#include <QThread>							//Qt Threading library to move Inssidious core to its own thread
#include <QtWidgets/QWidget>				//QWidgets 
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtWinExtras/QtWin>				//Qt Windows Extras for extendFrameIntoClientArea function
#include "Windowsx.h"						//Macros header for GET_X_LPARAM and GET_Y_LPARAM macros
#include "Dwmapi.h"							//DWM Api header for the DwmDefWindowProc function

#include "Widgets\HeaderWidget.h"			//Inssidious creates and draws the Header on the main window
#include "Widgets\StartWidget.h"			//Inssidious creates and draws the Startup widget on the main window

#include "Controllers\TabController.h"		//Inssidious creates and draws the tab controller on the main window

#pragma comment(lib, "Qt5Cored.lib")		//QT Core libary
#pragma comment(lib, "Qt5Guid.lib")			//QApplication library
#pragma comment(lib, "Qt5Widgetsd.lib")		//QWidgets library
#pragma comment(lib, "Qt5WinExtras.lib")	//QtWin library
#pragma comment(lib, "dwmapi.lib")			//DWM library



class InssidiousUi : public QWidget
{
	Q_OBJECT

public:
	InssidiousUi(QWidget *parent = 0);
	~InssidiousUi();

	public slots:
	//Receives a message from Core to trigger removing the Startup widget & showing the header and tab controller
	void onCoreStarted();

private:
	//Override nativeEvent to react to messages sent to our window, particularly for window drawing & dragging
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;


	InssidiousCore* inssidiousCore;			//Pointer to the Inssidious backend implemented in Core			

	HeaderWidget* headerWidget;				//Pointer to the Header widget that controls the Menu icon and Sid logo
	StartWidget* startupWidget;				//Pointer to the Start widget that displays on initial startup

	TabController* tabController;			//Pointer to the Tab Controller that owns device tabs


	QPalette backgroundPalette;
	QPixmap backgroundImage = QPixmap(
		":/InssidiousUi/Background.png");	//QPixmap for the Inssidious Background image
};

#endif // INSSIDIOUSUI_H