

#include "DivertController.h"

#include <InssidiousCore/TamperModules/TamperModule.h>
#include <timeapi.h>


#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)
#define DIVERT_MAX_PACKETSIZE 0xFFFF
#define DIVERT_CLOCK_WAIT_MS 10
#define DIVERT_QUEUE_LEN_MAX 8192
#define DIVERT_QUEUE_TIME_MAX 2048



DivertController::DivertController(QString MAC, void* tamperModulesConfig[NUM_TAMPER_TYPES], volatile bool tamperModulesActive[NUM_TAMPER_TYPES])
{

	/* Save copies of the constructor values */

	MACAddress = MAC;
	ppTamperModulesConfig = tamperModulesConfig;
	pTamperModulesActive = tamperModulesActive;
	

	/* Initialize the packet SLIST */

	packetSList = static_cast<PSLIST_HEADER>(_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT));
	InitializeSListHead(packetSList);


	/* Initialize the tamper modules */

	ppTamperModules = new TamperModule*[NUM_TAMPER_TYPES];
	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		ppTamperModules[i] = TamperModule::makeTamperModule(i, &(tamperModulesConfig[i]), packetSList);
	}


	/* Set the timer resolution */

	timeBeginPeriod(timerResolution);
}


void DivertController::run()
{

	QThread::exec();
}

void DivertController::onDivertStop(QString MACAddress)
{
	if (this->MACAddress != MACAddress)
	{
		/* This signal is meant for another DivertController */
		return;
	}

	HANDLE threads[5];
	threads[0] = readLoop1;
	threads[1] = readLoop2;
	threads[2] = readLoop3;
	threads[3] = readLoop4;
	threads[4] = clockThread;


	if (this->divertActive)
	{
		InterlockedDecrement16(&this->divertActive);

		WaitForMultipleObjects(5, threads, TRUE, INFINITE);
	}


	emit divertStopped(this->MACAddress);

}

void DivertController::onDivertUpdateIPAddress(QString MACAddress, QString IPAddress)
{
	if (this->MACAddress != MACAddress)
	{
		/* This signal is meant for another DivertController */
		return;
	}

	if (this->divertActive)
	{
		/* We're currently running. Stop the threads before restarting */

		HANDLE threads[5];
		threads[0] = readLoop1;
		threads[1] = readLoop2;
		threads[2] = readLoop3;
		threads[3] = readLoop4;
		threads[4] = clockThread;

		InterlockedDecrement16(&divertActive);

		WaitForMultipleObjects(5, threads, TRUE, INFINITE);

	}

	/* Update the filter string with the new IP address */

	srcAddrFilterString = QString("ip.SrcAddr == " + IPAddress);
	dstAddrFilterString = QString("ip.DstAddr == " + IPAddress);


	/* Open WinDivert handles */

	srcAddrDivertHandleLayerNetwork = WinDivertOpen(srcAddrFilterString.toLocal8Bit(), WINDIVERT_LAYER_NETWORK, 0, 0);
	if (srcAddrDivertHandleLayerNetwork == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();

		//TODO: Handle this error
		return;
	}

	srcAddrDivertHandleLayerNetworkForward = WinDivertOpen(srcAddrFilterString.toLocal8Bit(), WINDIVERT_LAYER_NETWORK_FORWARD, 0, 0);
	if (srcAddrDivertHandleLayerNetworkForward == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();

		//TODO: Handle this error
		return;
	}

	dstAddrDivertHandleLayerNetwork = WinDivertOpen(dstAddrFilterString.toLocal8Bit(), WINDIVERT_LAYER_NETWORK, 0, 0);
	if (dstAddrDivertHandleLayerNetwork == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();

		//TODO: Handle this error
		return;
	}

	dstAddrDivertHandleLayerNetworkForward = WinDivertOpen(dstAddrFilterString.toLocal8Bit(), WINDIVERT_LAYER_NETWORK_FORWARD, 0, 0);
	if (dstAddrDivertHandleLayerNetworkForward == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();

		//TODO: Handle this error
		return;
	}

	clockLoopDivertHandle = WinDivertOpen("icmpv6" /* for this handle, we do not care about the packets */, WINDIVERT_LAYER_NETWORK, 0, WINDIVERT_FLAG_SNIFF);
	if (clockLoopDivertHandle == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();

		//TODO: Handle this error
		return;
	}

	/* Max the WinDivert queue length and time */

	WinDivertSetParam(srcAddrDivertHandleLayerNetwork, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN_MAX);
	WinDivertSetParam(srcAddrDivertHandleLayerNetwork, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME_MAX);
	WinDivertSetParam(srcAddrDivertHandleLayerNetworkForward, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN_MAX);
	WinDivertSetParam(srcAddrDivertHandleLayerNetworkForward, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME_MAX);
	WinDivertSetParam(dstAddrDivertHandleLayerNetwork, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN_MAX);
	WinDivertSetParam(dstAddrDivertHandleLayerNetwork, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME_MAX);
	WinDivertSetParam(dstAddrDivertHandleLayerNetworkForward, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN_MAX);
	WinDivertSetParam(dstAddrDivertHandleLayerNetworkForward, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME_MAX);


	/* Minimize the clockLoop send handle */

	WinDivertSetParam(clockLoopDivertHandle, WINDIVERT_PARAM_QUEUE_LEN, 1 /*minimum queue length*/);
	WinDivertSetParam(clockLoopDivertHandle, WINDIVERT_PARAM_QUEUE_TIME, 128 /*minimum queue time*/);


	/* Start the Read and Tamper threads */

	InterlockedIncrement16(&this->divertActive);

	readLoop1 = CreateThread(nullptr, 1, reinterpret_cast<LPTHREAD_START_ROUTINE>(DivertReadLoop1), this, 0, nullptr);
	if (readLoop1 == nullptr)
	{
		HRESULT result = GetLastError();
		InterlockedDecrement16(&this->divertActive);

		//TODO: Handle this error
		return;
	}

	readLoop2 = CreateThread(nullptr, 1, reinterpret_cast<LPTHREAD_START_ROUTINE>(DivertReadLoop2), this, 0, nullptr);
	if (readLoop2 == nullptr)
	{
		HRESULT result = GetLastError();
		InterlockedDecrement16(&this->divertActive);

		//TODO: Handle this error
		return;
	}

	readLoop3 = CreateThread(nullptr, 1, reinterpret_cast<LPTHREAD_START_ROUTINE>(DivertReadLoop3), this, 0, nullptr);
	if (readLoop3 == nullptr)
	{
		HRESULT result = GetLastError();
		InterlockedDecrement16(&this->divertActive);

		//TODO: Handle this error
		return;
	}

	readLoop4 = CreateThread(nullptr, 1, reinterpret_cast<LPTHREAD_START_ROUTINE>(DivertReadLoop4), this, 0, nullptr);
	if (readLoop4 == nullptr)
	{
		HRESULT result = GetLastError();
		InterlockedDecrement16(&this->divertActive);

		//TODO: Handle this error
		return;
	}

	clockThread = CreateThread(nullptr, 1, reinterpret_cast<LPTHREAD_START_ROUTINE>(DivertClockLoop), this, 0, nullptr);
	if (clockThread == nullptr)
	{
		HRESULT result = GetLastError();
		InterlockedDecrement16(&this->divertActive);

		//TODO: Handle this error
		return;
	}


}

DWORD DivertController::DivertReadLoop1(void* pDivertControllerInstance)
{
	DivertController* This = static_cast<DivertController*>(pDivertControllerInstance);

	return This->divertReadLoop(This->srcAddrDivertHandleLayerNetwork);

}

DWORD DivertController::DivertReadLoop2(void* pDivertControllerInstance)
{
	DivertController* This = static_cast<DivertController*>(pDivertControllerInstance);

	return This->divertReadLoop(This->srcAddrDivertHandleLayerNetworkForward);

}

DWORD DivertController::DivertReadLoop3(void* pDivertControllerInstance)
{
	DivertController* This = static_cast<DivertController*>(pDivertControllerInstance);

	return This->divertReadLoop(This->dstAddrDivertHandleLayerNetwork);

}

DWORD DivertController::DivertReadLoop4(void* pDivertControllerInstance)
{
	DivertController* This = static_cast<DivertController*>(pDivertControllerInstance);

	return This->divertReadLoop(This->dstAddrDivertHandleLayerNetworkForward);

}


DWORD DivertController::divertReadLoop(HANDLE divertHandle)
{
	for (;;)
	{
		DivertPacket* dPacket = static_cast<DivertPacket*>(malloc(sizeof(DivertPacket)));
		if (!dPacket)
		{
			__debugbreak();
		}

		/* Wait for WinDivert to give us a packet */

		if (!WinDivertRecv(divertHandle, dPacket->packet, DIVERT_MAX_PACKETSIZE, &dPacket->addr, &dPacket->packetLength))
		{
			DWORD lastError = GetLastError();
			if (lastError == ERROR_INVALID_HANDLE || lastError == ERROR_OPERATION_ABORTED)
			{
				OutputDebugStringW(L"Handle died or operation aborted. Exit loop.\n");
				assert(true);
				return 0;
			}

			OutputDebugStringW(L"Failed to recv a packet. \n"/*, GetLastError()*/);
			assert(true);
			continue;
		}

		
		/* If we should have stopped while waiting for WinDivert, bail now */

		if (!this->divertActive)
		{
			return 0;
		}
		

		/* WFP does not guarantee a checksum; if there isn't one in the packet, set one now */

		WinDivertHelperCalcChecksums(dPacket->packet, dPacket->packetLength, WINDIVERT_HELPER_NO_REPLACE);


		/* Send the DivertPacket through each tamper module */

		for (int i = 0; i < NUM_TAMPER_TYPES - 1; i++)
		{
			if (!dPacket)
			{
				/* Packet was dropped or moved onto the SLIST */
				break;
			}
			if (pTamperModulesActive[i] == true)
			{
				ppTamperModules[i]->process(dPacket);
			}
		}
		

		/* If we still have a packet, send it */

		if (dPacket)
		{
			WinDivertSendEx(divertHandle, dPacket->packet, dPacket->packetLength, 0, &(dPacket->addr), nullptr, nullptr);
			free(dPacket);
			dPacket = nullptr;
		}
	}
}



DWORD DivertController::DivertClockLoop(void* pDivertControllerInstance)
{
	DivertController* This = static_cast<DivertController*>(pDivertControllerInstance);
	return This->divertClockLoop();
}




DWORD DivertController::divertClockLoop() 
{
	while (true)
	{
		if (!this->divertActive)
		{
			WinDivertClose(clockLoopDivertHandle);
			clockLoopDivertHandle = nullptr;


			/* Sleep for a bit and close any other still-open handles */

			Sleep(DIVERT_CLOCK_WAIT_MS);

			if (srcAddrDivertHandleLayerNetwork)
			{
				WinDivertClose(srcAddrDivertHandleLayerNetwork);
				srcAddrDivertHandleLayerNetwork = nullptr;
			}
			if (srcAddrDivertHandleLayerNetworkForward)
			{
				WinDivertClose(srcAddrDivertHandleLayerNetworkForward);
				srcAddrDivertHandleLayerNetworkForward = nullptr;
			}
			if (dstAddrDivertHandleLayerNetwork)
			{
				WinDivertClose(dstAddrDivertHandleLayerNetwork);
				dstAddrDivertHandleLayerNetwork = nullptr;
			}
			if (dstAddrDivertHandleLayerNetworkForward)
			{
				WinDivertClose(dstAddrDivertHandleLayerNetworkForward);
				dstAddrDivertHandleLayerNetworkForward = nullptr;
			}

			return 0;
		}

		/* Check for a packet on the list */

		PacketListEntry* pPacketEntry = reinterpret_cast<PacketListEntry*>(InterlockedPopEntrySList(packetSList));

		if (pPacketEntry == nullptr)
		{
			/* No packets on the list. Sleep, then continue looping */

			Sleep(DIVERT_CLOCK_WAIT_MS);
			continue;
		}


		/* At least one packet in the list */

		PSLIST_HEADER clockLoopSList = static_cast<PSLIST_HEADER>(_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT));
		InitializeSListHead(clockLoopSList);

		PSLIST_ENTRY entryFirst = nullptr;
		PSLIST_ENTRY entryLast = nullptr;
		int listCount = 0;

		do
		{
			if (pPacketEntry->releaseTimestamp < timeGetTime())
			{
				/* This packet is ready to be sent */

				WinDivertSendEx(clockLoopDivertHandle, pPacketEntry->packet, pPacketEntry->packetLength, 0, &(pPacketEntry->addr), nullptr, nullptr);
				_aligned_free(pPacketEntry);
				pPacketEntry = nullptr;
			}
			else
			{
				/* This packet needs to sit around for a bit longer. Add it to the clock loop slist */

				InterlockedPushEntrySList(clockLoopSList, &pPacketEntry->ItemEntry);
				listCount++;

				if (entryLast == nullptr)
				{
					entryLast = &pPacketEntry->ItemEntry;
				}

				pPacketEntry = nullptr;
			}

			/* Try to get another packet */

			pPacketEntry = reinterpret_cast<PacketListEntry*>(InterlockedPopEntrySList(packetSList));

		} while (pPacketEntry != nullptr);


		/* Push the list of packets that weren't yet ready for release back into the main packetSlist*/
		
		if (listCount > 0)
		{
			entryFirst = RtlFirstEntrySList(clockLoopSList);

			if (entryFirst && entryLast)
			{
				InterlockedPushListSList(packetSList, entryFirst, entryLast, listCount);
			}
		}


		_aligned_free(clockLoopSList);


		/* Loop again */
	}
}

