


#include "DivertController.h"


#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)
#define DIVERT_MAX_PACKETSIZE 0xFFFF
#define DIVERT_CLOCK_WAIT_MS 100
#define DIVERT_QUEUE_LEN 2 << 10
#define DIVERT_QUEUE_TIME 2 << 9 



DivertController::DivertController(QString MACAddress)
{

	MAC = MACAddress;
	packetList = new PacketList();

	tamperModule[LAG] = new LagModule();
	tamperModule[THROTTLE] = new ThrottleModule();
	tamperModule[RESET] = new ResetModule();
	tamperModule[JITTER] = new JitterModule();
	tamperModule[DROPPED_PACKETS] = new DropPacketsModule();
	tamperModule[CORRUPT_PACKETS] = new CorruptPacketsModule();
	tamperModule[NO_PACKETS] = new NoPacketsModule();
	tamperModule[NO_DNS] = new NoDNSModule();
	tamperModule[NO_SERVER] = new NoServerModule();
	tamperModule[NO_SSL] = new NoSSLModule();
	tamperModule[REDIR_TO_PORTAL] = new RedirToPortalModule();
	tamperModule[HTTP_HTTPS_ONLY] = new HTTPHTTPSOnlyModule();
	tamperModule[SITE_BLOCKED] = new SiteBlockedModule();

	enabled[LAG] = false;
	enabled[THROTTLE] = false;
	enabled[RESET] = false;
	enabled[JITTER] = false;
	enabled[DROPPED_PACKETS] = false;
	enabled[CORRUPT_PACKETS] = false;
	enabled[NO_PACKETS] = false;
	enabled[NO_DNS] = false;
	enabled[NO_SERVER] = false;
	enabled[NO_SSL] = false;
	enabled[REDIR_TO_PORTAL] = false;
	enabled[HTTP_HTTPS_ONLY] = false;
	enabled[SITE_BLOCKED] = false;
}


void DivertController::run()
{

	QString ipAddress;
	hasIPAddress = false;
	DWORD result = ERROR_SUCCESS;
	PMIB_IPNET_TABLE2 pIpNetTable = NULL;	
	char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };


	/* Loop until this device has an IP Address */

	int debugLoopVar = 0;
	do
	{
		debugLoopVar++;

		if (debugLoopVar > 100)
		{
			DebugBreak();
		}

		/* Sleep for a second */

		sleep(1);


		/* Get the IP Address to Physical Address table */

		result = GetIpNetTable2(AF_INET, &pIpNetTable);
		if (result != NO_ERROR)
		{
			result = GetLastError();
			//TODO: Handle this error

			return;
		}


		/* Loop through the entries in the table to find our MAC Address */

		for (int i = 0; i < pIpNetTable->NumEntries; i++)
		{

			/* Convert the MAC Address in the IpNetTable to a QString */

			QString tableMACAddress;
			for (uint j = 0; j < pIpNetTable->Table[i].PhysicalAddressLength; j++)
			{
				char lowbit = digits[(int)pIpNetTable->Table[i].PhysicalAddress[j] & 0xf];
				char highbit = digits[(int)((pIpNetTable->Table[i].PhysicalAddress[j] & 0xf0) >> 4)];
				tableMACAddress.append(highbit);
				tableMACAddress.append(lowbit);
				if (j != 5)
					tableMACAddress.append('-');
				
			}


			/* If the MAC Address matches the device we're here for, confirm the entry we see is valid */

			if (MAC == tableMACAddress)
			{
				MIB_IPNET_ROW2 ipNetRow = pIpNetTable->Table[i];

				/* NlnsReachable == pIpNetTable->Table[i].State ||  */
				if (S_OK == ResolveIpNetEntry2(&ipNetRow, NULL))
				{

					/* Save this as the IP Address and leave the loop */

					ipAddress = inet_ntoa(ipNetRow.Address.Ipv4.sin_addr);
					hasIPAddress = true;
				}
				else
				{
					
					/* The entry appears stale. Flush the table and loop again */

					if(NO_ERROR != FlushIpNetTable2(AF_INET, pIpNetTable->Table[i].InterfaceIndex))
					{
						//TODO: Handle this error

					}
				}


				/* In any case, if we found a MAC Address, break out of the table for loop */

				break;
			}
		}


		/* Continue looping until we get an IP address */

	} while (!hasIPAddress);


	/* Open a WinDivert handle */

	dbgFilterString = QString("ip.DstAddr == " + ipAddress + " and ip.SrcAddr != 192.168.25.1");
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

	QThread::exec();
}

DWORD DivertController::StaticReadLoopThreadStart(void* pDivertControllerInstance)
{
	DivertController* This = (DivertController*)pDivertControllerInstance;
	return This->divertReadLoop();
}

DWORD DivertController::StaticClockLoopThreadStart(void* pDivertControllerInstance)
{
	DivertController* This = (DivertController*)pDivertControllerInstance;
	return This->divertClockLoop();
}


int DivertController::sendAllListPackets() {
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
void DivertController::divertConsumeStep() {

#ifdef _DEBUG
	DWORD startTick = GetTickCount(), dt;
#endif

	for (int i = 0; i < NUM_TAMPER_TYPES - 1; i++)
	{
		if (this->enabled[i])
		{
			this->tamperModule[i]->process(packetList);
			//InterlockedIncrement16(&(module->processTriggered));
		}
	}

	int cnt = sendAllListPackets();

#ifdef _DEBUG
	dt = GetTickCount() - startTick;
	if (dt > DIVERT_CLOCK_WAIT_MS / 2) {
		//LOG("Costy consume step: %lu ms, sent %d packets", GetTickCount() - startTick, cnt);
	}
#endif
}

// periodically try to consume packets to keep the network responsive and not blocked by recv
DWORD DivertController::divertClockLoop() {
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

DWORD DivertController::divertReadLoop() {
	char packetBuf[DIVERT_MAX_PACKETSIZE];
	WINDIVERT_ADDRESS addrBuf;
	UINT readLen;
	Packet *pnode;
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

void DivertController::onDivertStop() {
	HANDLE threads[2];
	threads[0] = loopThread;
	threads[1] = clockThread;

	//LOG("Stopping...");
	InterlockedIncrement16(&stopLooping);
	WaitForMultipleObjects(2, threads, TRUE, INFINITE);

	//LOG("Successfully waited threads and stopped.");
}
