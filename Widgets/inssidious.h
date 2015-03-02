#ifndef INSSIDIOUS_H
#define INSSIDIOUS_H

#include <QWidget>
#include <QThread>
#include "ui_inssidious.h"
#include "StartupWidget\startupwidget.h"
#include "Core\core.h"

class Inssidious : public QWidget
{
	Q_OBJECT

public:
	Inssidious(QWidget *parent = 0);
	~Inssidious();



signals:


public slots :
	void onInssidiousStarted();
	void onDeviceConnected();					//A device connected. Add a device widget to sidebar
	void onDeviceDisconnected();				//A device disconnected. Remove device widget from sidebar
	void onShowDeviceWidget();					//A device widget was clicked. Hide all device widgets and then show that device widget

private:
	Ui::Inssidious ui;							
	StartupWidget* startupWidget;				//Pointer to an instance of Startup Widget
	Core* core;									//Pointer to an instance of Core
	QThread* coreThread;						//Pointer to the QThread to move Core to


	QVBoxLayout* tamperAreaNoDevicesLayout;		//Layout for Tamper Area Widget when no devices are connected
	QLabel* waitingForDevicesMessage;			//Message to display while waiting for devices to connect

};

#endif // INSSIDIOUS_H