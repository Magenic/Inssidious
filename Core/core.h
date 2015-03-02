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
	static bool getWirelessInterfaces(QList<QString>* foundWirelessInterfaces);
	static bool getAllNetworkInterfaces(QList<QString>* foundNetworkInterfaces);

public slots:
	void onThreadStart();
	void onInssidiousStart();

signals:
	void coreInitialized();
	void coreInitializeFailed(QString string);
	void coreStarted();
	void coreStartFailed(QString string);
	void inssidiousStarted();
	void inssidiousStartFailed(QString string);

private:

};

#endif // CORE_H
