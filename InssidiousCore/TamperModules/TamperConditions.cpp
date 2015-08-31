
#include "TamperConditions.h"


#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)

#define LAG_MIN "0"
#define LAG_MAX "3000"
#define KEEP_AT_MOST 2000
// send FLUSH_WHEN_FULL packets when buffer is full
#define FLUSH_WHEN_FULL 800
#define TIMER_RESOLUTION 4

short TamperConditions::process(PacketList* packetList)
{
	if (packetList->head == packetList->tail)
	{
		/* no packets */
		return 0;
	}


	Packet* dropHead = packetList->head;

	int dropped = 0;
	while (dropHead->next != packetList->tail) 
	{
        // chance in range of [0, 10000]
        if (/*checkDirection(pac->addr.Direction, dropInbound, dropOutbound) && */ calcChance(chance)) 
		{
            //LOG("dropped with chance %.1f%%, direction %s",
            //    chance/100.0, BOUND_TEXT(pac->addr.Direction));
			packetList->freeNode(packetList->popNode(dropHead));
            ++dropped;
        } 
		else 
		{
			dropHead = packetList->head->next;
        }
    }

    return dropped > 0;




	/* From Jitter
	

	DWORD currentTime = timeGetTime();
	Packet *pac = packetList->tail->prev;
	// pick up all packets and fill in the current time
	while (bufSize < KEEP_AT_MOST && pac != packetList->head) {
		if (true) {
			packetList->insertAfter(packetList->popNode(pac), bufHead)->timestamp = timeGetTime();
			++bufSize;
			pac = packetList->tail->prev;
		}
		else {
			pac = pac->prev;
		}
	}

	// try sending overdue packets from buffer tail
	while (!isBufEmpty()) {
		Packet *pac = bufTail->prev;
		if (currentTime > pac->timestamp + rand() % jitterVarianceInMs + 15) {
			packetList->insertAfter(packetList->popNode(bufTail->prev), packetList->head); // sending queue is already empty by now
			--bufSize;
			//LOG("Send lagged packets.");
		}
		else {
			//LOG("Sent some lagged packets, still have %d in buf", bufSize);
			break;
		}
	}

	// if buffer is full just flush things out
	if (bufSize >= KEEP_AT_MOST) {
		int flushCnt = FLUSH_WHEN_FULL;
		while (flushCnt-- > 0) {
			packetList->insertAfter(packetList->popNode(bufTail->prev), packetList->head);
			--bufSize;
		}
	}

	return bufSize > 0;
	
	*/




	/* From Reset 
	
	
	
	short reset = FALSE;
	Packet *pac = packetList->head->next;
	while (pac != packetList->tail) {
		if (pac->packetLen > TCP_MIN_SIZE
			&& (setNextCount || calcChance(chance)))
			{
				PWINDIVERT_TCPHDR pTcpHdr;
				WinDivertHelperParsePacket(
					pac->packet,
					pac->packetLen,
					NULL,
					NULL,
					NULL,
					NULL,
					&pTcpHdr,
					NULL,
					NULL,
					NULL);
	
				if (pTcpHdr != NULL) {
					//LOG("injecting reset w/ chance %.1f%%", chance / 100.0);
					pTcpHdr->Rst = 1;
					WinDivertHelperCalcChecksums(pac->packet, pac->packetLen, 0);
	
					reset = TRUE;
					if (setNextCount > 0) {
						InterlockedDecrement16(&setNextCount);
					}
				}
			}
	
		pac = pac->next;
	}

	return reset;

	
	
	
	*/


}

TamperConditions::TamperConditions(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
	jitterVarianceInMs = 50;

	if (bufHead->next == NULL && bufTail->next == NULL) {
		bufHead->next = bufTail;
		bufTail->prev = bufHead;
		bufSize = 0;
	}
	else {
		assert(isBufEmpty());
	}

	if (!resolutionSet) {
		// begin only fails when period out of range
		timeBeginPeriod(TIMER_RESOLUTION);
		resolutionSet = 1;
	}

}


TamperConditions::~TamperConditions()
{
	
}


inline short TamperConditions::isBufEmpty()
{
	short ret = bufHead->next == bufTail;
	if (ret) assert(bufSize == 0);
	return ret;
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



//TamperHTTPCorruptedResponse::TamperHTTPCorruptedResponse(void** ppTamperConfig)
//{
//	patterns[0] = 0x64;
//	patterns[1] = 0x13;
//	patterns[2] = 0x88;
//
//	patterns[3] = 0x40;
//	patterns[4] = 0x1F;
//	patterns[5] = 0xA0;
//
//	patterns[6] = 0xAA;
//	patterns[7] = 0x55;
//}
//
//inline void TamperHTTPCorruptedResponse::tamper_buf(char* buf, UINT len)
//{
//	UINT ix;
//	for (ix = 0; ix < len; ++ix) {
//		buf[ix] ^= patterns[patIx++ & 0x7];
//	}
//}
//
//short TamperHTTPCorruptedResponse::process(PacketList* packetList)
//{
//	short tampered = FALSE;
//	Packet *pac = packetList->head->next;
//	while (pac != packetList->tail) {
//		if (/*checkDirection(pac->addr.Direction, tamperInbound, tamperOutbound)*/
//			/*&& */calcChance(chance)) {
//			char *data = NULL;
//			UINT dataLen = 0;
//			if (WinDivertHelperParsePacket(pac->packet, pac->packetLen, NULL, NULL, NULL,
//				NULL, NULL, NULL, (PVOID*)&data, &dataLen)
//				&& data != NULL && dataLen != 0) {
//				// try to tamper the central part of the packet,
//				// since common packets put their checksum at head or tail
//				if (dataLen <= 4) {
//					// for short packet just tamper it all
//					tamper_buf(data, dataLen);
//					//LOG("tampered w/ chance %.1f, dochecksum: %d, short packet changed all", chance / 100.0, doChecksum);
//				}
//				else {
//					// for longer ones process 1/4 of the lens start somewhere in the middle
//					UINT len = dataLen;
//					UINT len_d4 = len / 4;
//					tamper_buf(data + len / 2 - len_d4 / 2 + 1, len_d4);
//					//LOG("tampered w/ chance %.1f, dochecksum: %d, changing %d bytes out of %u", chance / 100.0, doChecksum, len_d4, len);
//				}
//				// FIXME checksum seems to have some problem
//				if (doChecksum) {
//					WinDivertHelperCalcChecksums(pac->packet, pac->packetLen, 0);
//				}
//				tampered = TRUE;
//			}
//
//		}
//		pac = pac->next;
//	}
//	return tampered;
//}




















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
