
#include "TamperConditions.h"
#include "TamperTypes.h"

#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)

#define LAG_MIN "0"
#define LAG_MAX "3000"
#define KEEP_AT_MOST 2000
// send FLUSH_WHEN_FULL packets when buffer is full
#define FLUSH_WHEN_FULL 800
#define TIMER_RESOLUTION 4

TamperConditions::TamperConditions(void** ppTamperConfig)
{
	this->ppConditionsConfig = (short**)ppTamperConfig;
	
	
	/* Start a linked list to buffer packets in before re-injecting at a later time */

	this->conditionsHeadNode = Packet{ 0 };
	this->conditionsTailNode = Packet{ 0 };
	bufferHead->next = bufferTail;
	bufferTail->prev = bufferHead;
	bufferSize = 0;


	/* Fill the packet tamper patterns array */

	patterns[0] = 0x64;
	patterns[1] = 0x13;
	patterns[2] = 0x88;
	patterns[3] = 0x40;
	patterns[4] = 0x1F;
	patterns[5] = 0xA0;
	patterns[6] = 0xAA;
	patterns[7] = 0x55;


	/* Set a four second timer resolution for future timeGetTime calls */

	timeBeginPeriod(timerResolution);

}


TamperConditions::~TamperConditions()
{

}


short TamperConditions::process(PacketList* packetList)
{
	if (!**ppConditionsConfig || **ppConditionsConfig == 0)
	{
		/* No conditions set, don't process these packets */

		return 0;
	}

	if (packetList->head == packetList->tail)
	{
		/* No packets */

		return 0;
	}

	/* Loop through all packets in the list */

	Packet* pDivertPacket = packetList->head;
	while (pDivertPacket->next != packetList->tail)
	{
		if (calcChance(*ppConditionsConfig[CHANCE_LOSS]))
		{
			/* Drop this packet */
			packetList->freeNode(packetList->popNode(pDivertPacket));
		}
		else if (calcChance(*ppConditionsConfig[CHANCE_DELAY]))
		{
			/* Pull this packet into the delay buffer */

			packetList->insertAfter(packetList->popNode(pDivertPacket), bufferHead)->timestamp = timeGetTime() + delayTime;
			pDivertPacket = packetList->tail->prev;

			/* Increment the buffer size and the next packet's release time */

			++bufferSize;
		}
		else if (calcChance(*ppConditionsConfig[CHANCE_CORRUPT]))
		{
			char *data = nullptr;
			UINT dataLen = 0;

			/* Parse the packet for any data */

			if (WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen, 0, 0, 0, 0, 0, 0, (PVOID*)&data, &dataLen)
				&& data != nullptr && dataLen != 0)
			{
				/* Tamper all of a short packet */
	
				if (dataLen <= 4)
				{
					corruptPacket(data, dataLen);
				}
				else
				{
					/* Tamper somewhere near the middle */
					UINT len = dataLen;
					UINT len_d4 = len / 4;
					corruptPacket(data + len / 2 - len_d4 / 2 + 1, len_d4);
				}

				/* Do not recalculate the packet checksum so the receiver knows it is bad */

				//Perhaps offer the evil version, recalculating this, this one day
				//WinDivertHelperCalcChecksums(pDivertPacket->packet, pDivertPacket->packetLen, 0);
			}
		}
		else if (pDivertPacket->packetLen > TCP_MIN_SIZE && calcChance(*ppConditionsConfig[CHANCE_RESET]))
		{
			/* Set the TCP RESET flag on this packet */
			
			PWINDIVERT_TCPHDR pTcpHdr;
			WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen,	0, 0, 0, 0,	&pTcpHdr, 0, 0, 0);

			if (pTcpHdr) /* tcp header pointer is valid */
			{
				pTcpHdr->Rst = 1;
				WinDivertHelperCalcChecksums(pDivertPacket->packet, pDivertPacket->packetLen, 0);
			}
		}
		else
		{
			/* This packet survives */

			pDivertPacket = packetList->head->next;
		}
	}


	/* Send any packets that are overdue to go out from the delay chance */

	while (!isBufEmpty())
	{
		if (timeGetTime() > bufferTail->prev->timestamp)
		{
			packetList->insertAfter(packetList->popNode(bufferTail->prev), packetList->head);
			--bufferSize;
		}
	}


	return 0;

}




//class TamperHTTPCorruptedResponse : public TamperModule
//{
//public:
//	TamperHTTPCorruptedResponse(void** ppTamperConfig);
//	~TamperHTTPCorruptedResponse();
//	short process(PacketList* packetList) override;
//
//private:
//	void** ppTamperConfig;
//
//	volatile short chance = 1000; // [0 - 10000]
//	volatile short doChecksum = 1; // recompute checksum after after tampering
//
//	// patterns covers every bit
//	char patterns[8];
//	int patIx = 0; // put this here to give a more random results
//
//	inline void tamper_buf(char* buf, UINT len);
//};


//#include "TamperModule.h"
//
//class TamperDelay : public TamperModule
//{
//public:
//	TamperDelay(void** ppTamperConfig);
//	~TamperDelay();
//	short process(PacketList* packetList) override;
//
//private:
//	void** ppTamperConfig;
//
//	volatile short chance = 1000; // [0-10000]
//	short resolutionSet = 0;
//
//	// time frame in ms, when a throttle start the packets within the time 
//	// will be queued and sent altogether when time is over
//	volatile short throttleFrame;
//
//	Packet throttleHeadNode = Packet{ 0 }, throttleTailNode = Packet{ 0 };
//	Packet *bufHead = &throttleHeadNode, *bufTail = &throttleTailNode;
//	int bufSize = 0;
//	DWORD throttleStartTick = 0;
//
//	short isBufEmpty();
//
//};
//
//
//
//#include "TamperDelay.h"
//
//#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)
//
//#define NAME "throttle"
//#define TIME_MIN "0"
//#define TIME_MAX "1000"
//#define TIME_DEFAULT 30
//// threshold for how many packet to throttle at most
//#define KEEP_AT_MOST 1000
//#define TIMER_RESOLUTION 4
//
//TamperDelay::TamperDelay(void** ppTamperConfig)
//{
//	this->ppTamperConfig = ppTamperConfig;
//
//	throttleFrame = TIME_DEFAULT;
//
//	if (bufHead->next == NULL && bufTail->next == NULL) {
//		bufHead->next = bufTail;
//		bufTail->prev = bufHead;
//		bufSize = 0;
//	}
//	else {
//		assert(isBufEmpty());
//	}
//	throttleStartTick = 0;
//
//	if (!resolutionSet) {
//		// begin only fails when period out of range
//		timeBeginPeriod(TIMER_RESOLUTION);
//		resolutionSet = 1;
//	}
//
//}
//
//inline short TamperDelay::isBufEmpty()
//{
//	short ret = bufHead->next == bufTail;
//	if (ret) assert(bufSize == 0);
//	return ret;
//}
//
//short TamperDelay::process(PacketList* packetList)
//{
//	short throttled = FALSE;
//
//	if (!throttleStartTick) {
//		if (!packetList->isListEmpty() && calcChance(chance)) {
//			//LOG("Start new throttling w/ chance %.1f, time frame: %d", chance / 10.0, throttleFrame);
//			throttleStartTick = timeGetTime();
//			throttled = TRUE;
//			goto THROTTLE_START; // need this goto since maybe we'll start and stop at this single call
//		}
//	}
//	else {
//	THROTTLE_START:
//		// start a block for declaring local variables
//	{
//		// already throttling, keep filling up
//		Packet *pac = packetList->tail->prev;
//		DWORD currentTick = timeGetTime();
//		while (bufSize < KEEP_AT_MOST && pac != packetList->head) {
//			if (true /*checkDirection(pac->addr.Direction, throttleInbound, throttleOutbound)*/) {
//				packetList->insertAfter(packetList->popNode(pac), bufHead);
//				++bufSize;
//				pac = packetList->tail->prev;
//			}
//			else {
//				pac = pac->prev;
//			}
//		}
//
//		// send all when throttled enough, including in current step
//		if (bufSize >= KEEP_AT_MOST || (currentTick - throttleStartTick > (unsigned int)throttleFrame))
//		{
//			Packet *oldLast = packetList->tail->prev;
//			//LOG("Throttled end, send all %d packets. Buffer at max: %s", bufSize, bufSize == KEEP_AT_MOST ? "YES" : "NO");
//			while (!isBufEmpty())
//			{
//				packetList->insertAfter(packetList->popNode(bufTail->prev), oldLast);
//				--bufSize;
//			}
//			throttleStartTick = 0;
//		}
//	}
//	}
//
//	return throttled;
//}
//
//
//TamperDelay::~TamperDelay()
//{
//
//}
