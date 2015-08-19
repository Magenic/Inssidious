#ifndef TAMPERCONTROLLER_H
#define TAMPERCONTROLLER_H

#include <QObject>

#include "DivertController.h"


class Divert;

class TamperController : public QObject
{
	Q_OBJECT

public:
	TamperController();
	~TamperController();

signals:
	void coreTamperStarted(QString MACAddress, QString TamperType);
	void coreTamperStopped(QString MACAddress, QString TamperType);

public slots:
	void onCoreAddDevice(QString MACAddress);
	void onCoreDropDevice(QString MACAddress);

	void onCoreTamperStart(QString MACAddress, QString TamperType);
	void onCoreTamperStop(QString MACAddress, QString TamperType);

private:

	QList<DivertController*>tcDeviceList;

};

#endif // TAMPERCONTROLLER_H
