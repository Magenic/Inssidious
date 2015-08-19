#ifndef TAMPERCONTROLLER_H
#define TAMPERCONTROLLER_H

#include <QObject>

#include "DivertController.h"
#include "TamperTypes.h"


class TamperController : public QObject
{
	Q_OBJECT

public:
	TamperController();
	~TamperController();

signals:
	void coreTamperStarted(QString MACAddress, TamperType tamperType);
	void coreTamperStopped(QString MACAddress, TamperType tamperType);

public slots:
	void onCoreAddDevice(QString MACAddress);
	void onCoreDropDevice(QString MACAddress);

	void onCoreTamperStart(QString MACAddress, TamperType tamperType);
	void onCoreTamperStop(QString MACAddress, TamperType tamperType);

private:

	QList<DivertController*>tcDeviceList;

};

#endif // TAMPERCONTROLLER_H
