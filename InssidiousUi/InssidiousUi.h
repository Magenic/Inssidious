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

#include <QThread>							//Qt Threading library to move Inssidious core to its own thread
#include <QtWidgets/QWidget>				//QWidgets 
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtWinExtras/QtWin>				//Qt Windows Extras for extendFrameIntoClientArea function
#include "Windowsx.h"						//Macros header for GET_X_LPARAM and GET_Y_LPARAM macros
#include "Dwmapi.h"							//DWM Api header for the DwmDefWindowProc function

#include "Widgets\StartWidget.h"			//Inssidious creates and draws the Startup widget on the main window

#include "Controllers\UiDeviceController.h"		//Inssidious creates and draws the tab controller on the main window

#ifdef _DEBUG
#pragma comment(lib, "Qt5Cored.lib")		//QT Core libary
#pragma comment(lib, "Qt5Guid.lib")			//QApplication library
#pragma comment(lib, "Qt5Widgetsd.lib")		//QWidgets library
#pragma comment(lib, "Qt5WinExtrasd.lib")	//QtWin library
#endif
#ifndef _DEBUG
#pragma comment(lib, "Qt5Core.lib")			//QT Core libary
#pragma comment(lib, "Qt5Gui.lib")			//QApplication library
#pragma comment(lib, "Qt5Widgets.lib")		//QWidgets library
#pragma comment(lib, "Qt5WinExtras.lib")	//QtWin library
#endif

#pragma comment(lib, "dwmapi.lib")			//DWM library



class InssidiousUi : public QWidget
{
	Q_OBJECT

public:
	InssidiousUi(QWidget *parent = 0);


private:

	QPalette backgroundPalette;
	QPixmap backgroundImageLaunch = QPixmap(":/InssidiousUi/BackgroundLaunch.png");
	QPixmap backgroundImageRunning = QPixmap(":/InssidiousUi/BackgroundRunning.png");

	QPushButton *pushButtonClose;
	QPushButton *pushButtonMinimize;

	QString closeStyleSheet = 
		"QPushButton{image: url(:/InssidiousUi/CloseDefault.png); border: none;}\
		QPushButton:hover{image: url(:/InssidiousUi/CloseHover.png); border: none; }\
		QPushButton:pressed{image: url(:/InssidiousUi/ClosePressed.png); border: none; }";

	QString minimizeStyleSheet = 
		"QPushButton{image: url(:/InssidiousUi/MinimizeDefault.png); border: none;}\
		QPushButton:hover{image: url(:/InssidiousUi/MinimizeHover.png); border: none; }\
		QPushButton:pressed{image: url(:/InssidiousUi/MinimizePressed.png); border: none; }";


	QLabel networkName;
	QLabel networkNameIcon;
	QLabel networkPassword;
	QLabel networkPasswordIcon;
	QPalette textPalette;

	/* Inssidious creates instances of the core backend, Start Widget, and Tab Controller */

	InssidiousCore* inssidiousCore;
	StartWidget* startWidget;
	UiDeviceController* uiDeviceController;


	/* Inssidious implements the nativeEvent function to react to window messages and handle drawing & dragging */

	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;


private slots:
	
	void onUiStartCore(QString networkName, QString networkPassword, QString networkAdapter);
	void onCoreStarting(QString messageText, bool isErrorMessage = false);
	void onCoreStarted();
	void onCoreStopped();

	void onCoreAddDevice(QString MACAddress);
	void onCoreDropDevice(QString MACAddress);
	
	void onUiTamperStart(QString MACAddress, TamperType tamperType, void* pTamperConfig);
	void onUiTamperStop(QString MACAddress, TamperType tamperType);

	void onMinimizeClicked();
	void onSettingsClicked();

signals:
	void coreStart(QString networkName, QString networkPassword, QString networkAdapter);
	void uiUpdateStartingText(QString messageText, bool isErrorMessage = false);

	void uiAddDevice(QString MACAddress);
	void uiDropDevice(QString MACAddress);

	void coreStartTamper(QString MACAddress, int tamperType, void* pTamperConfig);
	void coreStopTamper(QString MACAddress, int tamperType);

};

#endif // INSSIDIOUSUI_H