#ifndef DEVICE_H
#define DEVICE_H

#include <QObject> 
#include "Core\types.h"
#include "Widgets\DeviceWidgets\devicewidget.h"
#include "Widgets\TamperWidgets\tamperwidget.h"


class Device : public QObject
{
	Q_OBJECT

public:
	Device(QString, QWidget*);				//Device MAC Address and MainAreaWidget pointer
	~Device();

	void select();
	void unselect();

	bool isActive = false;

	QString* MACAddress;
	DeviceWidget* widget;

	QWidget* tamperWidgetsContainer;

signals:


public slots:
	//void onEnableTamper();
	//void onDisableTamper();
	//void onTamperActivity();

private slots:
	void onTamperWidgetClicked(TamperType);

private:
	QGridLayout* containerLayout;

	TamperWidget* NetworkLag;
	TamperWidget* DropAllTraffic;
	TamperWidget* DropNonHttpTraffic;
	TamperWidget* RedirectToPortal;
	TamperWidget* WebServiceError;
	TamperWidget* WebServiceTimeOut;
	TamperWidget* WebServiceEmptyResponses;


	int totalActiveTamperCount;

};

#endif // DEVICE_H
