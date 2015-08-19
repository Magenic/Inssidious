


#include "PacketController.h"
#include "PacketList.h"

#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)
#define DIVERT_MAX_PACKETSIZE 0xFFFF
#define DIVERT_CLOCK_WAIT_MS 100
#define DIVERT_QUEUE_LEN 2 << 10
#define DIVERT_QUEUE_TIME 2 << 9 


PacketController::PacketController()
{
	drop = new PacketTamperModule();
	drop->enabledFlag = 0;
}

void PacketController::run()
{
	QThread::exec();
}

DWORD PacketController::StaticReadLoopThreadStart(void* pPacketControllerInstance)
{
	PacketController* This = (PacketController*)pPacketControllerInstance;
	return This->divertReadLoop();
}

DWORD PacketController::StaticClockLoopThreadStart(void* pPacketControllerInstance)
{
	PacketController* This = (PacketController*)pPacketControllerInstance;
	return This->divertClockLoop();
}

void PacketController::onPacketControllerStart(QString MACAddress, bool * pHasIPAddress)
{

	//
	*pHasIPAddress = false;
	DWORD result = ERROR_SUCCESS;
	PMIB_IPNETTABLE pIpNetTable = NULL;
	DWORD dwSize = 0;
	QString ipAddress;
	char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	/* Loop until this device has an IP Address */

	do
	{
		/* Sleep for a second */

		sleep(1);


		/* Get the size required by GetIpNetTable and allocate the memory */

		result = GetIpNetTable(NULL, &dwSize, 0);
		if (result == ERROR_INSUFFICIENT_BUFFER)
		{
			pIpNetTable = (MIB_IPNETTABLE *)malloc(dwSize);
		}
		else
		{
			result = GetLastError();
			//TODO: Handle this error

			return;
		}
		

		/* Get the IP Address to Physical Address table */

		result = GetIpNetTable(pIpNetTable, &dwSize, 0);
		if (result != NO_ERROR) 
		{
			result = GetLastError();
			//TODO: Handle this error

			return;
		}


		/* Loop through the entries in the table to find our MAC Address */
		
		for (int i = 0; i < pIpNetTable->dwNumEntries; i++) 
		{

			/* If we find a matching MAC Address, convert and save the IP Address string and flag that we have an IP */
			QString tableMAC;
			for (uint k = 0; k < 6; k++)
			{
				char lowbit = digits[(int)pIpNetTable->table[i].bPhysAddr[k] & 0xf];
				char highbit = digits[(int)((pIpNetTable->table[i].bPhysAddr[k] & 0xf0) >> 4)];
				tableMAC.push_back(highbit);
				tableMAC.push_back(lowbit);
				if (k != 5)
					tableMAC.push_back('-');
			}
			
			if (MACAddress == tableMAC)
			{
				struct in_addr addr;
				addr.s_addr = (long)pIpNetTable->table[i].dwAddr;
				ipAddress = inet_ntoa(addr);
				*pHasIPAddress = true;
			}

		}

		/* Free the memory we allocated for pIpNetTable */

		free(pIpNetTable);


		/* Continue looping until we get an IP address */

	} while (!*pHasIPAddress);


	/* Open a WinDivert handle */
	QByteArray byteArray = QString("ip.DstAddr == " + ipAddress + " and ip.SrcAddr != 192.168.25.1").toLocal8Bit();
	const char * pFilterString = byteArray.data();

	divertHandle = WinDivertOpen(pFilterString, WINDIVERT_LAYER_NETWORK, 0, 0);
	if (divertHandle == INVALID_HANDLE_VALUE)
	{
		result = GetLastError();

		//TODO: Handle this error
		return;
	}


	WinDivertSetParam(divertHandle, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN);
	WinDivertSetParam(divertHandle, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME);
	//LOG("WinDivert internal queue Len: %d, queue time: %d", QUEUE_LEN, QUEUE_TIME);


	
	// init package link list
	packetList = new PacketList();
	packetList->initPacketNodeList();



	// kick off the loop
	//LOG("Creating threads and mutex...");
	stopLooping = FALSE;
	mutex = CreateMutex(NULL, FALSE, NULL);
	if (mutex == NULL) 
	{
		result = GetLastError();

		//TODO: Handle this error
		return;
	}

	loopThread = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)StaticReadLoopThreadStart, this, 0, NULL);
	if (loopThread == NULL)
	{
		result = GetLastError();

		//TODO: Handle this error
		return;
	}

	clockThread = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)StaticClockLoopThreadStart, this, 0, NULL);
	if (clockThread == NULL) 
	{
		result = GetLastError();

		//TODO: Handle this error
		return;
	}
}


int PacketController::sendAllListPackets() {
	// send packet from tail to head and remove sent ones
	int sendCount = 0;
	UINT sendLen;
	PacketList::PacketNode *pnode;

#ifdef _DEBUG
	// check the list is good
	// might go into dead loop but it's better for debugging
	PacketList::PacketNode *p = packetList->head;
	do {
		p = p->next;
	} while (p->next);
	assert(p == packetList->tail);
#endif

	while (!packetList->isListEmpty()) {
		pnode = packetList->popNode(packetList->tail->prev);
		sendLen = 0;
		assert(pnode != packetList->head);
		// FIXME inbound injection on any kind of packet is failing with a very high percentage
		//       need to contact windivert auther and wait for next release
		if (!WinDivertSend(divertHandle, pnode->packet, pnode->packetLen, &(pnode->addr), &sendLen)) {
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
void PacketController::divertConsumeStep() {
#ifdef _DEBUG
	DWORD startTick = GetTickCount(), dt;
#endif
	int ix, cnt;

	drop->process(packetList);

	// use lastEnabled to keep track of module starting up and closing down
	//for (ix = 0; ix < moduleCount; ++ix) {
		//PacketTamperModule *module = modules[ix];
		/*if (*(module->enabledFlag)) {
			if (!module->lastEnabled) {
				module->startUp();
				module->lastEnabled = 1;
			}*/
			//if (module->process(packetList)) {
				//InterlockedIncrement16(&(module->processTriggered));
			//}
		//}
		//else {
		//	if (module->lastEnabled) {
		//		module->closeDown(head, tail);
		//		module->lastEnabled = 0;
		//	}
		//}
	//}
	cnt = sendAllListPackets();
#ifdef _DEBUG
	dt = GetTickCount() - startTick;
	if (dt > DIVERT_CLOCK_WAIT_MS / 2) {
		//LOG("Costy consume step: %lu ms, sent %d packets", GetTickCount() - startTick, cnt);
	}
#endif
}

// periodically try to consume packets to keep the network responsive and not blocked by recv
DWORD PacketController::divertClockLoop() {
	DWORD startTick, stepTick, waitResult;
	int ix;

	for (;;) {
		// use acquire as wait for yielding thread
		startTick = GetTickCount();
		waitResult = WaitForSingleObject(mutex, DIVERT_CLOCK_WAIT_MS);
		switch (waitResult) {
		case WAIT_OBJECT_0:
			/***************** enter critical region ************************/
			divertConsumeStep();
			/***************** leave critical region ************************/
			if (!ReleaseMutex(mutex)) {
				InterlockedIncrement16(&stopLooping);
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
			InterlockedIncrement16(&stopLooping);
			break;
		case WAIT_FAILED:
			//LOG("Acquire failed (%lu)", GetLastError());
			InterlockedIncrement16(&stopLooping);
			break;
		}

		// need to get the lock here
		if (stopLooping) {
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
				closed = WinDivertClose(divertHandle);
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

DWORD PacketController::divertReadLoop() {
	char packetBuf[DIVERT_MAX_PACKETSIZE];
	WINDIVERT_ADDRESS addrBuf;
	UINT readLen;
	PacketList::PacketNode *pnode;
	DWORD waitResult;


	for (;;) {
		// each step must fully consume the list
		assert(packetList->isListEmpty()); // FIXME has failed this assert before. don't know why
		if (!WinDivertRecv(divertHandle, packetBuf, DIVERT_MAX_PACKETSIZE, &addrBuf, &readLen)) {
			DWORD lastError = GetLastError();
			if (lastError == ERROR_INVALID_HANDLE || lastError == ERROR_OPERATION_ABORTED) {
				// treat closing handle as quit
				//LOG("Handle died or operation aborted. Exit loop.");
				assert(true);
				return 0;
			}
			//LOG("Failed to recv a packet. (%lu)", GetLastError());
			assert(true);
			continue;
		}
		if (readLen > DIVERT_MAX_PACKETSIZE) {
			// don't know how this can happen
			//LOG("Internal Error: DivertRecv truncated recv packet.");
			assert(true);
		}

		waitResult = WaitForSingleObject(mutex, INFINITE);
		switch (waitResult) {
		case WAIT_OBJECT_0:
			/***************** enter critical region ************************/
			if (stopLooping) {
				//LOG("Lost last recved packet but user stopped. Stop read loop.");
				/***************** leave critical region ************************/
				if (!ReleaseMutex(mutex)) {
					//LOG("Fatal: Failed to release mutex on stopping (%lu). Will stop anyway.", GetLastError());
					assert(true);
				}
				return 0;
			}
			// create node and put it into the list
			pnode = packetList->createNode(packetBuf, readLen, &addrBuf);
			packetList->appendNode(pnode);
			divertConsumeStep();
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

void PacketController::divertStop() {
	HANDLE threads[2];
	threads[0] = loopThread;
	threads[1] = clockThread;

	//LOG("Stopping...");
	InterlockedIncrement16(&stopLooping);
	WaitForMultipleObjects(2, threads, TRUE, INFINITE);

	//LOG("Successfully waited threads and stopped.");
}
