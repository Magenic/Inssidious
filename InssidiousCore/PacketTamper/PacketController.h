


#ifndef PACKETCONTROLLER_H
#define PACKETCONTROLLER_H

#include <QThread>						//Base of PacketController

#include <Ws2tcpip.h>					//Types used with WinDivert when handling packets
#include <Iphlpapi.h>					//Types used with WinDivert & functions to obtain the IP Address from MAC Address
#include <mmsystem.h>					//Time APIs used during synchronization

#include "PacketTamperModule.h"

class PacketList;

class PacketController : public QThread
{
	Q_OBJECT


public:
	PacketController();
	void run();

	//TEMP
	static const int moduleCount = 1;

	
	/* Public functions to start and stop packet capturing */

	//void divertStart(QString MACAddress, bool * pHasIPAddress);
	void divertStop();


	PacketTamperModule* drop; // all modules in a list

public slots:
	void onPacketControllerStart(QString MACAddress, bool * pHasIPAddress);
	

private:

	PacketList* packetList;

	/* PacketController creates additional threads to process packets captured by WinDivert*/
	/* Static functions to pass to CreateThread to call instance specific functions */

	static DWORD StaticReadLoopThreadStart(void* pPacketControllerInstance);
	static DWORD StaticClockLoopThreadStart(void* pPacketControllerInstance);
	DWORD divertReadLoop();
	DWORD divertClockLoop();


	/* Handles to the WinDivert instance, the two threads, and the synchronization mutex */
	
	HANDLE divertHandle, loopThread, clockThread, mutex;


	/* Variable is watched for an atomically-increased change when we need close up the threads */
	
	volatile short stopLooping = FALSE;


	// step function to let module process and consume all packets on the list
	void divertConsumeStep();

	// sends all packets on the list
	int sendAllListPackets();




};

#endif // PACKETCONTROLLER_H
