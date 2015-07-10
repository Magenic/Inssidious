#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QString>
#include <QUuid>
#include <WinSock2.h>
#include <Windows.h>						//Windows types
#include <Wlanapi.h>						//Wlan functions 
#include <wtypes.h>							//Wlan types
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
	
	static QList<NetworkAdapter> NetworkAdapterList;				//List of ethernet and wireless internet connections
	
public slots:
	void onThreadStarted();											//Fires when Core's thread starts, performs basic initialization work
	void onCoreStartRouter(QString, QString, QString);				//Triggered by a signal from Startup Widget, contains wireless name, password, and internet connection adapter
	void onRouterFailed(QString);									//Triggered by Router if something ever goes wrong

signals:
	void coreReadyToStart();										//Notify Startup Widget that Core is on it's own thread and ready to start

	void coreRouterStarted(QString, QString);						//Notify InssidiousUi that the router started successfully. Pass along network name and password
	void coreFailed(QString);										//Notify InssidiousUi of a critical core failure

	void coreDeviceConnected(QString);								//Notify InssidiousUi of a device connection
	void coreDeviceDisconnected(QString);							//Notify InssidiousUi of a device disconnection

private:
	bool runningAsAdmin();											//Confirm we are running as an Admin, return false if not
	bool runningOnWindows7OrNewer();								//Confirm we are running on Windows 7 or newer, return false if not
	bool getNetworkAdapters();										//Populate NetworkAdapterList with list of network adapters

};





#endif // CORE_H
