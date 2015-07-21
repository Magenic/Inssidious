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

#include "tab.h"							//Tab Controller owns the creation and deletion of tabs

class TabController : public QWidget
{
	Q_OBJECT

public:
	TabController(QWidget *parent);
	~TabController();


public slots:
	void onDeviceConnected(QString MACaddress);		//Receives notifications to create a tab when a device has connected
	void onDeviceDisconnected(QString MACaddress);	//Receives notifications to delete a tab when a device has disconnected


private slots:
	void onTabClicked(Tab* tab);					//Receive notifications to switch to a different active tab


private:
	QList<Tab*> tcTabList;							//Private list of all tab objects, identified by pointer or MAC

	QPalette tcPaletteDevicesPresent;				//Palette used to define the background image of the tab controller
	QPalette tcPaletteNoDevices;					//Palette used to define the background image of the tab controller

	QPixmap tcBackgroundImageDevicesPresent = QPixmap(":/Tabs/TabsDevicesPresent.png");	//Draws a bordered rectangle
	QPixmap tcBackgroundImageNoDevices = QPixmap(":/Tabs/TabsNoDevices.png");			//Draws Waiting for Devices text

};

#endif // TABCONTROLLER_H
