#ifndef INSSIDIOUS_H
#define INSSIDIOUS_H

#include <QWidget>
#include <QThread>
#include "ui_inssidious.h"
#include "Core\types.h"
#include "Core\core.h"
#include "Device\device.h"
#include "DeviceWidgets\devicewidget.h"
#include "StartupWidget\startupwidget.h"
#include "TamperWidgets\tamperwidget.h"


class InssidiousUi : public QWidget
{
	Q_OBJECT

public:
	InssidiousUi(QWidget *parent = 0);


public slots :
	void onCoreRouterStarted(QString, QString);				//Core has started the router. Hide the Startup Widget and show Waiting for Devices message
	void onCoreFailed(QString);								//Core has hit a critical error. Display an error message asking to restart Inssidious.

	void onDeviceConnected(QString MACAddress);				//A device connected. Add a device widget to sidebar & device to device list
	void onDeviceDisconnected(QString MACAddress);			//A device disconnected. Remove device widget from sidebar & device from device list


private:
	Ui::Template ui;										//Instance of the ui template from file ./Widgets/inssidious.ui
	Core* core;												//Pointer to an instance of Core
	QThread* coreThread;									//Pointer to the QThread to move Core to

	StartupWidget* startupWidget;							//Pointer to an instance of Startup Widget

	QVBoxLayout* waitingForDevicesLayout;					//Layout for Waiting For Devices Widget when Inssidious first starts
	QLabel* waitingForDevicesMessage;						//Message to display when no devices are connected	

	QVBoxLayout* criticalErrorLayout;						//Layout for errors that require restarting Inssidious
	QLabel* criticalErrorSadLogo;							//Sad version of the Inssidious logo to display when there is a critical error
	QLabel* criticalErrorMessage;							//Message to display when there is a critical error
	QPushButton* criticalErrorQuitButton;					//Button to quit Inssidious after a critical error

	QList<Device*> DeviceList;								//List of all device objects

private slots:
	void onDeviceWidgetClicked(DeviceWidget*);				//A device widget was clicked. Hide all device widgets and then show that device widget
};

#endif // INSSIDIOUS_H