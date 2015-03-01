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
	void showDeviceWidget();					//Hide all device widgets and then show device widget
	void deviceConnected();						//Add a device widget to sidebar
	void deviceDisconnected();					//Remove device widget from sidebar


private:
	Ui::Inssidious ui;
	StartupWidget* startupWidget;						//Pointer to an instance of the Startup Widget
	Core* core;
	QThread* coreThread;

};

#endif // INSSIDIOUS_H