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


private:

	QPalette backgroundPalette;
	QPixmap backgroundImage = QPixmap(":/InssidiousUi/Background.png");


	/* Inssidious creates instances of the core backend, Header Widget, Start Widget, and Tab Controller */

	InssidiousCore* inssidiousCore;
	HeaderWidget* headerWidget;
	StartWidget* startWidget;
	TabController* tabController;


	/* Inssidious implements the nativeEvent function to react to window messages and handle drawing & dragging */

	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;


private slots:
	
	void onUiStartCore(QString networkName, QString networkPassword, QString networkAdapter);
	void onCoreStarting(QString messageText, bool isErrorMessage = false);
	void onCoreStarted();
	void onCoreStopped();

	void onCoreAddDevice(QString MACAddress);
	void onCoreDropDevice(QString MACAddress);
	
	void onUiTamperStart(QString MACAddress, TamperType tamperType);
	void onUiTamperStop(QString MACAddress, TamperType tamperType);
	void onCoreTamperStarted(QString MACAddress, TamperType tamperType);
	void onCoreTamperStopped(QString MACAddress, TamperType tamperType);

signals:
	void coreStart(QString networkName, QString networkPassword, QString networkAdapter);
	void uiUpdateStartingText(QString messageText, bool isErrorMessage = false);

	void uiAddDevice(QString MACAddress);
	void uiDropDevice(QString MACAddress);

	void coreStartTamper(QString MACAddress, int tamperType);
	void coreStopTamper(QString MACAddress, int tamperType);
	void uiTamperStarted(QString MACAddress, TamperType tamperType);
	void uiTamperStopped(QString MACAddress, TamperType tamperType);
};

#endif // INSSIDIOUSUI_H