#include <InssidiousCore/TamperModules/TamperBase.h>

#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)

#define LAG_MIN "0"
#define LAG_MAX "3000"
#define KEEP_AT_MOST 2000
// send FLUSH_WHEN_FULL packets when buffer is full
#define FLUSH_WHEN_FULL 800
#define TIMER_RESOLUTION 4

short TamperQuality::process(PacketList* packetList)
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

TamperQuality::TamperQuality()
{
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


TamperQuality::~TamperQuality()
{
	
}


inline short TamperQuality::isBufEmpty()
{
	short ret = bufHead->next == bufTail;
	if (ret) assert(bufSize == 0);
	return ret;
}

