#ifndef TAMPERCONTROLLER_H
#define TAMPERCONTROLLER_H

#include <QObject>

#include "Tamper\TamperComponent.h"

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
	struct tcDevice{
		QString MAC;
		TamperComponent* tc[7];
	};

	QList<tcDevice*>tcDeviceList;

};

#endif // TAMPERCONTROLLER_H
