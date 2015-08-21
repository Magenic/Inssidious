#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>

#include "DivertController.h"


class DeviceController : public QObject
{
	Q_OBJECT

public:
	DeviceController();
	~DeviceController();

signals:
	void coreTamperStarted(QString MACAddress, TamperType tamperType);
	void coreTamperStopped(QString MACAddress, TamperType tamperType);

public slots:
	void onCoreAddDevice(QString MACAddress);
	void onCoreDropDevice(QString MACAddress);

	void onCoreTamperStart(QString MACAddress, TamperType tamperType);
	void onCoreTamperStop(QString MACAddress, TamperType tamperType);

private:

	QList<DivertController*>deviceList;

};

#endif // DEVICECONTROLLER_H
