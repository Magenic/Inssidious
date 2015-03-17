#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QString>
#include <QUuid>
#include <WinSock2.h>
#include <Windows.h>						//Windows types
#include <Wlanapi.h>						//Wlan functions 
#include <wtypes.h>						//Wlan types
#include <iphlpapi.h>						//IP Helper APIs
#include <comdef.h>							//Easy HRESULT conversion

#include "Core\types.h"						//Network Adapter and AdapterPhysType types
#include "Router\router.h"					//Router class to call when InssidiousUi asks to start

#pragma comment(lib, "iphlpapi.lib")		//Link against iphlpapi.lib for IP Helper APIs
#pragma comment(lib, "wlanapi.lib")			//Link against wlanapi.lib for the wlan APIs

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x)) 
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))



class Core : public QObject
{
	Q_OBJECT

public:
	Core();
	~Core();
	
	
	static QList<NetworkAdapter> NetworkAdapterList;
	

public slots:
	void onThreadStarted();
	void onCoreStartInssidious(int, int, QString, QString);
	void onRouterFailed(QString);
	//void onRouterDeviceConnected(QString);
	//void onRouterDeviceDisconnected(QString);

signals:
	void coreReadyToStart();

	void coreStarted(QString networkName, QString networkPassword);
	void coreFailed(QString errorMessage);			

	void coreDeviceConnected(QString);
	void coreDeviceDisconnected(QString);

private:
	bool runningAsAdmin();
	bool runningOnWindows7OrNewer();
	bool getNetworkAdapters();

};





#endif // CORE_H
