#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H

#include <QtWidgets/QWidget>				//QWidgets
#include <QtWidgets/QLayout>				//Layouts for QWidgets

#include "tab.h"

class TabController : public QWidget
{
	Q_OBJECT

public:
	TabController(QWidget *parent);
	~TabController();


public slots:
	void onDeviceConnected(QString MACaddress);
	void onDeviceDisconnected(QString MACaddress);


private slots:
	void onTabClicked(Tab* tab);


private:
	QList<Tab*> tcTabList;

	QPalette tcPaletteDevicesPresent;
	QPalette tcPaletteNoDevices;
	QPixmap tcBackgroundImageDevicesPresent = QPixmap(":/Tabs/TabsDevicesPresent.png");
	QPixmap tcBackgroundImageNoDevices = QPixmap(":/Tabs/TabsNoDevices.png");

};

#endif // TABCONTROLLER_H
