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

public slots:
	void onDeviceConnected(QString MACAddress);
	void onDeviceDisconnected(QString MACAddress);


private:
	struct tcDevice{
		QString MAC;
	};

	QList<tcDevice*>tcDeviceList;
};

#endif // TAMPERCONTROLLER_H
