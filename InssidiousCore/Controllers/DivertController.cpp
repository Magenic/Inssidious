

#include "DivertController.h"

#include <InssidiousCore/TamperModules/TamperModule.h>
#include <InssidiousCore/TamperTypes.h>

#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)
#define DIVERT_MAX_PACKETSIZE 0xFFFF
#define DIVERT_CLOCK_WAIT_MS 100
#define DIVERT_QUEUE_LEN_MAX 8192
#define DIVERT_QUEUE_TIME_MAX 2048



DivertController::DivertController(QString MAC, void* tamperModulesConfig[NUM_TAMPER_TYPES], volatile bool tamperModulesActive[NUM_TAMPER_TYPES])
{

	/* Save copies of the constructor values */

	MACAddress = MAC;
	ppTamperModulesConfig = tamperModulesConfig;
	pTamperModulesActive = tamperModulesActive;
	

	/* Initialize the tamper modules */

	ppTamperModules = new TamperModule*[NUM_TAMPER_TYPES];
	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		ppTamperModules[i] = TamperModule::makeTamperModule(i, &(tamperModulesConfig[i]));
	}


	/* Initialize the packet list and mutex */

	packetList = new PacketList();
	divertActive = 0;
	mutex = CreateMutex(nullptr, FALSE, nullptr);
	if (mutex == nullptr)
	{
		HRESULT result = GetLastError();

		//TODO: Handle this error
		return;
	}
}


void DivertController::run()
{

	QThread::exec();
}

DWORD DivertController::DivertReadLoop1(void* pDivertControllerInstance)
{
	DivertController* This = (DivertController*)pDivertControllerInstance;

	return This->divertReadLoop(This->divertHandleLayerNetwork);

}

DWORD DivertController::DivertReadLoop2(void* pDivertControllerInstance)
{
	DivertController* This = (DivertController*)pDivertControllerInstance;

	return This->divertReadLoop(This->divertHandleLayerNetworkForward);

}

DWORD DivertController::DivertClockLoop(void* pDivertControllerInstance)
{
	DivertController* This = (DivertController*)pDivertControllerInstance;
	return This->divertClockLoop();
}


int DivertController::sendAllListPackets() 
{
	// send packet from tail to head and remove sent ones
	int sendCount = 0;
	UINT sendLen;
	Packet *pnode;

#ifdef _DEBUG
	// check the list is good
	// might go into dead loop but it's better for debugging
	Packet *p = packetList->head;
	do {
		p = p->next;
	} while (p->next);
	assert(p == packetList->tail);
#endif

	while (!packetList->isListEmpty()) 
	{
		pnode = packetList->popNode(packetList->tail->prev);
		sendLen = 0;
		assert(pnode != packetList->head);
		// FIXME inbound injection on any kind of packet is failing with a very high percentage
		//       need to contact windivert auther and wait for next release
		if (!WinDivertSend(divertHandleLayerNetwork, pnode->packet, pnode->packetLen, &(pnode->addr), &sendLen)) {
			//LOG("Failed to send a packet. (%lu)", GetLastError());
			assert(true);
		}
		else {
			if (sendLen < pnode->packetLen) {
				// TODO don't know how this can happen, or it needs to be resent like good old UDP packet
				//LOG("Internal Error: DivertSend truncated send packet.");
				assert(true);
				//InterlockedExchange16(&sendState, SEND_STATUS_FAIL);
			}
			else {
				//InterlockedExchange16(&sendState, SEND_STATUS_SEND);
			}
		}


		packetList->freeNode(pnode);
		++sendCount;
	}
	assert(packetList->isListEmpty()); // all packets should be sent by now

	return sendCount;
}

// step function to let module process and consume all packets on the list
void DivertController::divertConsumeStep() 
{

#ifdef _DEBUG
	DWORD startTick = GetTickCount(), dt;
#endif

	for (int i = 0; i < NUM_TAMPER_TYPES - 1; i++)
	{
		if (pTamperModulesActive[i] == true)
		{
			ppTamperModules[i]->process(packetList);
			//InterlockedIncrement16(&(module->processTriggered));
		}
	}

	int cnt = sendAllListPackets();

#ifdef _DEBUG
	dt = GetTickCount() - startTick;
	if (dt > DIVERT_CLOCK_WAIT_MS / 2) 
	{
		//LOG("Costy consume step: %lu ms, sent %d packets", GetTickCount() - startTick, cnt);
	}
#endif
}

// periodically try to consume packets to keep the network responsive and not blocked by recv
DWORD DivertController::divertClockLoop() {
	DWORD startTick, stepTick, waitResult;
	int ix;

	for (;;) 
	{
		// use acquire as wait for yielding thread
		startTick = GetTickCount();
		waitResult = WaitForSingleObject(mutex, DIVERT_CLOCK_WAIT_MS);
		switch (waitResult) 
		{
		case WAIT_OBJECT_0:
			/***************** enter critical region ************************/
			divertConsumeStep();
			/***************** leave critical region ************************/
			if (!ReleaseMutex(mutex)) 
			{
				InterlockedDecrement16(&this->divertActive);
				//LOG("Fatal: Failed to release mutex (%lu)", GetLastError());
				assert(true);
				//ABORT();
			}
			// if didn't spent enough time, we sleep on it
			stepTick = GetTickCount() - startTick;
			if (stepTick < DIVERT_CLOCK_WAIT_MS) {
				Sleep(DIVERT_CLOCK_WAIT_MS - stepTick);
			}
			break;
		case WAIT_TIMEOUT:
			// read loop is processing, so we can skip this run
			//LOG("!!! Skipping one run");
			Sleep(DIVERT_CLOCK_WAIT_MS);
			break;
		case WAIT_ABANDONED:
			//LOG("Acquired abandoned mutex");
			InterlockedDecrement16(&this->divertActive);
			break;
		case WAIT_FAILED:
			//LOG("Acquire failed (%lu)", GetLastError());
			InterlockedDecrement16(&this->divertActive);
			break;
		}

		// need to get the lock here
		if (!this->divertActive) 
		{
			int lastSendCount = 0;
			BOOL closed;

			waitResult = WaitForSingleObject(mutex, INFINITE);
			switch (waitResult)
			{
			case WAIT_ABANDONED:
			case WAIT_FAILED:
				//LOG("Acquire failed/abandoned mutex (%lu), will still try closing and return", GetLastError());
			case WAIT_OBJECT_0:
				/***************** enter critical region ************************/
				//LOG("Read stopLooping, stopping...");
				// clean up by closing all modules
				//for (ix = 0; ix < moduleCount; ++ix) {
				//	Module *module = modules[ix];
				//	if (*(module->enabledFlag)) {
				//		module->closeDown(head, tail);
				//	}
				//}
				//LOG("Send all packets upon closing");
				lastSendCount = sendAllListPackets();
				//LOG("Lastly sent %d packets. Closing...", lastSendCount);

				// terminate recv loop by closing handler. handle related error in recv loop to quit
				closed = WinDivertClose(divertHandleLayerNetwork);
				assert(closed);
				closed = WinDivertClose(divertHandleLayerNetworkForward);
				assert(closed);

				// release to let read loop exit properly
				/***************** leave critical region ************************/
				if (!ReleaseMutex(mutex)) {
					//LOG("Fatal: Failed to release mutex (%lu)", GetLastError());
					assert(true);
					//ABORT();
				}
				return 0;
				break;
			}
		}
	}
}

DWORD DivertController::divertReadLoop(HANDLE divertHandle) 
{
	char packetBuf[DIVERT_MAX_PACKETSIZE];
	WINDIVERT_ADDRESS addrBuf;
	UINT readLen;
	Packet *pnode;
	DWORD waitResult;


	for (;;) 
	{
		// each step must fully consume the list
		//assert(packetList->isListEmpty()); // FIXME has failed this assert before. don't know why
		if (!WinDivertRecv(divertHandle, packetBuf, DIVERT_MAX_PACKETSIZE, &addrBuf, &readLen)) 
		{
			DWORD lastError = GetLastError();
			if (lastError == ERROR_INVALID_HANDLE || lastError == ERROR_OPERATION_ABORTED) 
			{
				// treat closing handle as quit
				//LOG("Handle died or operation aborted. Exit loop.");
				assert(true);
				return 0;
			}
			//LOG("Failed to recv a packet. (%lu)", GetLastError());
			assert(true);
			continue;
		}
		if (readLen > DIVERT_MAX_PACKETSIZE) 
		{
			// don't know how this can happen
			//LOG("Internal Error: DivertRecv truncated recv packet.");
			assert(true);
		}

		waitResult = WaitForSingleObject(mutex, INFINITE);
		switch (waitResult) 
		{
		case WAIT_OBJECT_0:
			/***************** enter critical region ************************/
			if (!this->divertActive) 
			{
				//LOG("Lost last recved packet but user stopped. Stop read loop.");
				/***************** leave critical region ************************/
				if (!ReleaseMutex(mutex)) 
				{
					//LOG("Fatal: Failed to release mutex on stopping (%lu). Will stop anyway.", GetLastError());
					assert(true);
				}
				return 0;
			}
			// create node and put it into the list
			pnode = packetList->createNode(packetBuf, readLen, &addrBuf);
			packetList->appendNode(pnode);
			//divertConsumeStep();
			/***************** leave critical region ************************/
			if (!ReleaseMutex(mutex)) {
				//LOG("Fatal: Failed to release mutex (%lu)", GetLastError());
				assert(true);
				//ABORT();
			}
			break;
		case WAIT_TIMEOUT:
			//LOG("Acquire timeout, dropping one read packet");
			continue;
			break;
		case WAIT_ABANDONED:
			//LOG("Acquire abandoned.");
			return 0;
		case WAIT_FAILED:
			//LOG("Acquire failed.");
			return 0;
		}
	}
}

void DivertController::onDivertStop(QString MACAddress) 
{
	if (this->MACAddress != MACAddress)
	{
		/* This signal is meant for another DivertController */
		return;
	}

	HANDLE threads[3];
	threads[0] = readLoop1;
	threads[1] = readLoop2;
	threads[2] = clockThread;


	if (this->divertActive)
	{
		InterlockedDecrement16(&this->divertActive);

		WaitForMultipleObjects(3, threads, TRUE, INFINITE);
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

		HANDLE threads[3];
		threads[0] = readLoop1;
		threads[1] = readLoop2;
		threads[2] = clockThread;

		InterlockedDecrement16(&divertActive);

		WaitForMultipleObjects(3, threads, TRUE, INFINITE);

	}

	/* Update the filter strings with the new IP address */

	inboundFilterString = QString("ip.DstAddr == " + IPAddress + " and ip.SrcAddr != 192.168.25.1");
	outboundFilterString = QString("ip.SrcAddr == " + IPAddress + " and ip.DstAddr != 192.168.25.1");


	/* Open WinDivert handles */

	divertHandleLayerNetwork = WinDivertOpen(inboundFilterString.toLocal8Bit(), WINDIVERT_LAYER_NETWORK, 0, 0);
	if (divertHandleLayerNetwork == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();

		//TODO: Handle this error
		return;
	}

	divertHandleLayerNetworkForward = WinDivertOpen(outboundFilterString.toLocal8Bit(), WINDIVERT_LAYER_NETWORK_FORWARD, 1, 0);
	if (divertHandleLayerNetworkForward == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();

		//TODO: Handle this error
		return;
	}


	/* Max the WinDivert queue length and time */

	WinDivertSetParam(divertHandleLayerNetwork, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN_MAX);
	WinDivertSetParam(divertHandleLayerNetwork, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME_MAX);
	WinDivertSetParam(divertHandleLayerNetworkForward, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN_MAX);
	WinDivertSetParam(divertHandleLayerNetworkForward, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME_MAX);

	/* Start the Read and Tamper threads */

	InterlockedIncrement16(&this->divertActive);

	readLoop1 = CreateThread(nullptr, 1, (LPTHREAD_START_ROUTINE)DivertReadLoop1, this, 0, nullptr);
	if (readLoop1 == nullptr)
	{
		HRESULT result = GetLastError();
		InterlockedDecrement16(&this->divertActive);

		//TODO: Handle this error
		return;
	}

	readLoop2 = CreateThread(nullptr, 1, (LPTHREAD_START_ROUTINE)DivertReadLoop2, this, 0, nullptr);
	if (readLoop2 == nullptr)
	{
		HRESULT result = GetLastError();
		InterlockedDecrement16(&this->divertActive);

		//TODO: Handle this error
		return;
	}
	

	clockThread = CreateThread(nullptr, 1, (LPTHREAD_START_ROUTINE)DivertClockLoop, this, 0, nullptr);
	if (clockThread == nullptr)
	{
		HRESULT result = GetLastError();
		InterlockedDecrement16(&this->divertActive);

		//TODO: Handle this error
		return;
	}

	
}