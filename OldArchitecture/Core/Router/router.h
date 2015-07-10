#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QUuid>

#include <Windows.h>						//Windows types
#include <Wlanapi.h>						//Wlan functions
#include <wtypes.h>							//Wlan types
#include <comdef.h>							//Easy HRESULT conversion



class Router : public QObject
{
	Q_OBJECT

public:
	Router();
	~Router();
	bool start(QString, QString);

	static void __stdcall WlanNotificationCallback(PWLAN_NOTIFICATION_DATA, PVOID);


signals:
	void routerFailed(QString);

	void deviceConnected(QString);
	void deviceDisconnected(QString);

private:
	HANDLE wlanHandle;						//Handle to call WlanQueryInterface to check interface capabilities
	static bool routerHasStarted;			//Bool for use in Wlan notifications around hosted network state changes
	GUID virtualWirelessDeviceGUID;			//Store the GUID of the virtual wireless device broadcasting the hosted network
};

#endif // ROUTER_H
