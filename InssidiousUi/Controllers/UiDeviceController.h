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

#include "Widgets\TabWidget.h"				//
#include "Widgets\TamperWidget.h"


class UiDeviceController : public QWidget
{
	Q_OBJECT

public:
	UiDeviceController(QWidget *parent);
	~UiDeviceController();


signals:
	void uiTamperStart(QString MACAddress, TamperType tamperType, void* pTamperConfig);
	void uiTamperStop(QString MACAddress, TamperType tamperType);


public slots:
	void onUiAddDevice(QString MACAddress);		//Receives notifications to create a tab when a device has connected
	void onUiDropDevice(QString MACAddress);	//Receives notifications to delete a tab when a device has disconnected


private slots:
	void onTabClicked(TabWidget* tab);						//Receive notifications to switch to a different active tab
	void onTamperStart(TamperWidget*, TamperType, void* pTamperConfig);
	void onTamperStop(TamperWidget* , TamperType);


private:

	struct device
	{
		QString MAC;									//MAC Address as the unique identifier
		TabWidget* tab;									//Tab widget to sit in the side bar
		TamperWidget* tamper;
	};
	
	QList<device*> deviceList;

};

#endif // TABCONTROLLER_H
