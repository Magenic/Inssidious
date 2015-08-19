/*
*  File:		tabcontroller.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H

#include <QtWidgets/QWidget>				//Base class of TabController
#include <QtWidgets/QLayout>				//Layouts for QWidgets

#include "Widgets\TabWidget.h"				//
#include "Widgets\TamperWidget.h"			//


class TabController : public QWidget
{
	Q_OBJECT

public:
	TabController(QWidget *parent);
	~TabController();


signals:
	void uiTamperStart(QString MACAddress, TamperType tamperType);
	void uiTamperStop(QString MACAddress, TamperType tamperType);


public slots:
	void onUiAddDevice(QString MACAddress);		//Receives notifications to create a tab when a device has connected
	void onUiDropDevice(QString MACAddress);	//Receives notifications to delete a tab when a device has disconnected

	void onUiTamperStarted(QString MACAddress, TamperType tamperType);
	void onUiTamperStopped(QString MACAddress, TamperType tamperType);


private slots:
	void onTabClicked(TabWidget* tab);						//Receive notifications to switch to a different active tab
	void onTamperWidgetClicked(TamperWidget* tamperButton);

private:
	struct tcDevice{
		QString MAC;
		TabWidget* tab;
		QWidget* tbContainer;
		QGridLayout* tbGridLayout;
		TamperWidget* tb[7];
	};
	
	QList<tcDevice*> tcDeviceList;

	QPalette tcPaletteDevicesPresent;				//Palette used to define the background image of the tab controller
	QPalette tcPaletteNoDevices;					//Palette used to define the background image of the tab controller

	QPixmap tcBackgroundImageDevicesPresent = QPixmap(":/Tabs/TabsDevicesPresent.png");	//Draws a bordered rectangle
	QPixmap tcBackgroundImageNoDevices = QPixmap(":/Tabs/TabsNoDevices.png");			//Draws Waiting for Devices text

};

#endif // TABCONTROLLER_H
