#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QString>
#include <WinSock2.h>
#include <Windows.h>						//Windows types
#include <Wlanapi.h>						//Wlan functions 
#include <wtypes.h>							//Wlan types
#include <iphlpapi.h>						//IP Helper APIs
#include <comdef.h>							//Easy HRESULT conversion

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
	
	
	static enum AdapterPhysTypes{ ETHERNET, WIRELESS, ERRORMESSAGE };	//Adapter types
	struct NetworkAdapter												//Network Adapter information
	{
		QString AdapterName;
		QString AdapterDescription;
		AdapterPhysTypes AdapterPhysType;
	};
	
	static QList<NetworkAdapter> Core::getNetworkAdapters();	//Store all ethernet & wireless interfaces in QList

public slots:
	void onThreadStarted();
	void onCoreStartInssidious();

signals:
	void coreThreadReady();
	void inssidiousStarted();

	void inssidiousCriticalError(QString string);		//Critical error signal should block further action

private:
	
};





#endif // CORE_H
