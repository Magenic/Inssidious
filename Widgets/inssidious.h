#ifndef INSSIDIOUS_H
#define INSSIDIOUS_H

#include <QWidget>
#include <QThread>
#include "ui_inssidious.h"
#include "Core\core.h"
#include "StartupWidget\startupwidget.h"
#include "deviceobject.h"


class Inssidious : public QWidget
{
	Q_OBJECT

public:
	Inssidious(QWidget *parent = 0);
	~Inssidious();

signals:


public slots :
	void onInssidiousStarted();					//Hide Startup Widget and show waiting for devices message
	void onDeviceConnected();					//A device connected. Add a device widget to sidebar
	void onDeviceDisconnected();				//A device disconnected. Remove device widget from sidebar
	void onSwitchDeviceWidgets(DeviceObject*);	//A device widget was clicked. Hide all device widgets and then show that device widget

	void onInssidiousCriticalError(QString);	//A critical error has occured. Display an error message asking to restart Inssidious.

private:
	Ui::Inssidious ui;							
	StartupWidget* startupWidget;				//Pointer to an instance of Startup Widget
	Core* core;									//Pointer to an instance of Core
	QThread* coreThread;						//Pointer to the QThread to move Core to

	QVBoxLayout* waitingForDevicesLayout;		//Layout for Waiting For Devices Widget when Inssidious first starts
	QLabel* waitingForDevicesMessage;			//Message to display when no devices are connected	

	QVBoxLayout* criticalErrorLayout;			//Layout for errors that require restarting Inssidious
	QLabel* criticalErrorSadLogo;				//Sad version of the Inssidious logo to display when there is a critical error
	QLabel* criticalErrorMessage;				//Message to display when there is a critical error
	QPushButton* criticalErrorQuitButton;		//Button to quit Inssidious after a critical error

	QList<DeviceObject*> deviceObjectList;		//List of all device objects
};

#endif // INSSIDIOUS_H