


#include "DivertController.h"


#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)
#define DIVERT_MAX_PACKETSIZE 0xFFFF
#define DIVERT_CLOCK_WAIT_MS 100
#define DIVERT_QUEUE_LEN_MAX 8192
#define DIVERT_QUEUE_TIME_MAX 2048



DivertController::DivertController(device * d)
{

	parentDevice = d;

	packetList = new PacketList();


	tamperModule[SPEED] = new LagModule();
	tamperModule[DELAY] = new ThrottleModule();
	tamperModule[QUALITY] = new ResetModule();
	tamperModule[REDIR_TO_PORAL] = new JitterModule();
	tamperModule[CONTENT_BLOCKED] = new DropPacketsModule();
	tamperModule[HTTP_HTTPS_ONLY] = new CorruptPacketsModule();
	tamperModule[NO_INTERNET] = new NoPacketsModule();
	tamperModule[NO_DNS] = new NoDNSModule();
	tamperModule[NO_SERVER] = new NoServerModule();
	tamperModule[HTTP_TIME_OUT] = new RedirToPortalModule();
	tamperModule[HTTP_UNEXPECTED_RESPONSE] = new HTTPHTTPSOnlyModule();
	tamperModule[HTTP_CORRUPTED_RESPONSE] = new SiteBlockedModule();

}


void DivertController::run()
{
	this->createThreads();

	QThread::exec();
}

void DivertController::createThreads()
{
	inboundFilterString = QString("ip.DstAddr == " + parentDevice->IPAddress + " and ip.SrcAddr != 192.168.25.1");
	outboundFilterString = QString("ip.SrcAddr == " + parentDevice->IPAddress + " and ip.DstAddr != 192.168.25.1");


	DWORD result = ERROR_SUCCESS;

	/* Open a WinDivert handle */


	divertHandle = WinDivertOpen(inboundFilterString.toLocal8Bit(), WINDIVERT_LAYER_NETWORK, 0, 0);
	if (divertHandle == INVALID_HANDLE_VALUE)
	{
		result = GetLastError();

		//TODO: Handle this error
		return;
	}


	WinDivertSetParam(divertHandle, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN_MAX);
	WinDivertSetParam(divertHandle, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME_MAX);
	//LOG("WinDivert internal queue Len: %d, queue time: %d", QUEUE_LEN, QUEUE_TIME);



	// kick off the loop
	//LOG("Creating threads and mutex...");
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
		if (this->parentDevice->enabled[i])
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
				InterlockedIncrement16(&(parentDevice->stop));
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
			InterlockedIncrement16(&(parentDevice->stop));
			break;
		case WAIT_FAILED:
			//LOG("Acquire failed (%lu)", GetLastError());
			InterlockedIncrement16(&(parentDevice->stop));
			break;
		}

		// need to get the lock here
		if (parentDevice->stop) 
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
			if (parentDevice->stop) 
			{
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
	InterlockedIncrement16(&(parentDevice->stop));
	WaitForMultipleObjects(2, threads, TRUE, INFINITE);

	//LOG("Successfully waited threads and stopped.");

	if (parentDevice)
	{
		emit divertStopped(parentDevice->MACAddress);
	}
}
