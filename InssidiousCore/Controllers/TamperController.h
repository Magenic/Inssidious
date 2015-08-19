#ifndef TAMPERCONTROLLER_H
#define TAMPERCONTROLLER_H

#include <QObject>

#include "PacketTamper\PacketController.h"


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
	void packetControllerStart(QString, bool *);

public slots:
	void onCoreAddDevice(QString MACAddress);
	void onCoreDropDevice(QString MACAddress);

	void onCoreTamperStart(QString MACAddress, QString TamperType);
	void onCoreTamperStop(QString MACAddress, QString TamperType);

private:
	struct tcDevice{
		QString MAC;
		bool hasIPAddress;
		PacketController* divert;
	};

	QList<tcDevice*>tcDeviceList;

};

#endif // TAMPERCONTROLLER_H
