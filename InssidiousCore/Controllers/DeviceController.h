#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>

#include <InssidiousCore/TamperTypes.h>


class DivertController;
class TamperModule;

class DeviceController : public QObject
{
	Q_OBJECT

public:
	DeviceController();
	~DeviceController();

signals:
	void divertStop(QString MACAddress);
	void divertUpdateIPAddress(QString MACAddress, QString IPAddress);


public slots:
	void onCoreAddDevice(QString MACAddress);
	void onCoreDropDevice(QString MACAddress);
	void onCoreUpdateDevice(QString MACAddress, QString ipAddress);

	void onCoreTamperStart(QString MACAddress, TamperType tamperType, void* pTamperConfig);
	void onCoreTamperStop(QString MACAddress, TamperType tamperType);

private slots:
	void onDivertStopped(QString MACAddress);


private:

	struct device
	{
		QString MACAddress;
		QString IPAddress;

		void* tamperModuleConfig[NUM_TAMPER_TYPES];
		volatile bool tamperModuleActive[NUM_TAMPER_TYPES];
		
		DivertController* divertController;
	};

	QList<device*>deviceList;
	QList<device*>pendingDeletionList;


	struct MAC_IP_Pair
	{
		QString MACAddress;
		QString ipAddress;
	};

	QList <MAC_IP_Pair*> lostPairs;
};

#endif // DEVICECONTROLLER_H
