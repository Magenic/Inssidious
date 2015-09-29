#ifndef DIVERTCONTROLLER_H
#define DIVERTCONTROLLER_H


#include <QThread>						//Base of DivertController
#include <InssidiousCore/TamperModules/PacketList.h>


class TamperModule;

class DivertController : public QThread
{
	Q_OBJECT


public:
	DivertController(QString, void*[], volatile bool[]);	

signals:
	void divertStopped(QString MACAddress);

public slots:
	void onDivertStop(QString MACAddress);
	void onDivertUpdateIPAddress(QString MACAddress, QString IPAddress);

private:

	/* QThread class calls run as the first thing executed as the new thread */
	/* Do initialization work like identifying IP address here and opening WinDivert handle */

	void run() override;


	/* Copies of the values sent in the constructor */

	QString MACAddress;
	void** ppTamperModulesConfig;
	volatile bool* pTamperModulesActive;



	TamperModule** ppTamperModules;
	PSLIST_HEADER packetSList;

	/* Lagged Packets are inserted into a list  */

	//SLIST PacketList* laggedPackets;


	/* Volatile short checked by all active threads to know when to stop */

	volatile short divertActive = 0;


	/* The divert filter strings, handles to the WinDivert instances, and handles to the divert threads */

	QString srcAddrFilterString;
	QString dstAddrFilterString;
	HANDLE srcAddrDivertHandleLayerNetwork = 0;
	HANDLE srcAddrDivertHandleLayerNetworkForward = 0;
	HANDLE dstAddrDivertHandleLayerNetwork = 0;
	HANDLE dstAddrDivertHandleLayerNetworkForward = 0;
	HANDLE clockLoopDivertHandle = 0;

	HANDLE readLoop1, readLoop2, readLoop3, readLoop4, clockThread = 0;


	/* Functions to create threads to process packets captured by WinDivert */
	/* Static functions to pass to CreateThread that fire the instance-specific function */

	static DWORD DivertReadLoop1(void* pDivertControllerInstance);
	static DWORD DivertReadLoop2(void* pDivertControllerInstance);
	static DWORD DivertReadLoop3(void* pDivertControllerInstance);
	static DWORD DivertReadLoop4(void* pDivertControllerInstance);
	static DWORD DivertClockLoop(void* pDivertControllerInstance);

	DWORD divertReadLoop(HANDLE divertHandle);
	DWORD divertClockLoop();


	UINT timerResolution = 4;
};

#endif // DIVERTCONTROLLER_H
