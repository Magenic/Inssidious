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
#include <QtWidgets/QButtonGroup>

#include "Widgets\TamperWidget.h"
#include "Widgets\NewDeviceWidget.h"

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
	void onTabClicked(int id);						//Receive notifications to switch to a different active tab
	void onSetDeviceInfo(QString MACAddress, QString deviceName, QString deviceType);
	void onTamperStart(TamperWidget*, TamperType, void* pTamperConfig);
	void onTamperStop(TamperWidget* , TamperType);


private:

	struct device
	{
		QString MAC;
		QPushButton* tab;
		TamperWidget* tamper;
		NewDeviceWidget* newDevice;
		bool named;
	};
	
	QList<device*> deviceList;
	QButtonGroup* tabGroup;

	QWidget* greenLine;

	QString tabStyleSheet =
		"QPushButton { margin: 0px; padding: 0px; background-color: #FCFFFC; color:#333333; font-family: 'Segoe UI'; font-size:15px; font-weight:400; text-decoration:none; border-width: 1px; border-style: solid; border-top: none; border-left: none; border-right-color: #4E9E38; border-bottom: 1px solid #4E9E38; }\
		QPushButton:hover:!pressed { background-color: #E6F2E6; border-top: none; border-left: none; border-right-color: #4E9E38; border-bottom: 1px solid #4E9E38;}\
		QPushButton:pressed{ background-color: #72C55D; border-top: none; border-left: none; border-right-color: #4E9E38; border-bottom: 1px solid #4E9E38;}\
		QPushButton:on { background-color: #EAEDF2; border-top: none; border-left: none; border-right-color: #4E9E38; border-bottom: none; }\
		QPushButton:on:hover:!pressed{ background-color: #E6F2E6; border-top: none; border-left: none; border-right-color: #4E9E38; border-bottom: none;}\
		QPushButton:on:pressed{ background-color: #72C55D; border-top: none; border-left: none; border-right-color: #4E9E38; border-bottom: none;}";
};

#endif // TABCONTROLLER_H
