#include "TamperSpeed.h"

#include "TamperTypes.h"

#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)


#define KEEP_AT_MOST 2000
// send FLUSH_WHEN_FULL packets when buffer is full
#define FLUSH_WHEN_FULL 800
#define TIMER_RESOLUTION 4


TamperSpeed::TamperSpeed(void** ppTamperConfig)
{
	this->ppSpeedTime = (short**)ppTamperConfig;


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

TamperSpeed::~TamperSpeed()
{
	
}

inline short TamperSpeed::isBufEmpty()
{
		short ret = bufHead->next == bufTail;
		if (ret) assert(bufSize == 0);
		return ret;
}

short TamperSpeed::process(PacketList* packetList)
{

	if (!**ppSpeedTime || **ppSpeedTime == 0)
	{
		/* No speed type set (yet?) or it's set to max, don't process these packets */

		return 0;
	}

	DWORD currentTime = timeGetTime();

	Packet *pac = packetList->tail->prev;

	// pick up all packets and fill in the release time
	DWORD releaseTime = timeGetTime();
	while (bufSize < KEEP_AT_MOST && pac != packetList->head) 
	{
		packetList->insertAfter(packetList->popNode(pac), bufHead)->timestamp = releaseTime;
		++bufSize;
		releaseTime += TamperSpeedTimes[**ppSpeedTime];
		pac = packetList->tail->prev;
	}


	// try sending overdue packets from buffer tail
	while (!isBufEmpty()) 
	{
		Packet *pac = bufTail->prev;
		if (currentTime > pac->timestamp)
		{
			packetList->insertAfter(packetList->popNode(bufTail->prev), packetList->head); // sending queue is already empty by now
			--bufSize;
			//LOG("Send lagged packets.");
		}
		else 
		{
			//LOG("Sent some lagged packets, still have %d in buf", bufSize);
			break;
		}
	}

	// if buffer is full just flush things out
	if (bufSize >= KEEP_AT_MOST) 
	{
		int flushCnt = FLUSH_WHEN_FULL;
		while (flushCnt-- > 0) 
		{
			packetList->insertAfter(packetList->popNode(bufTail->prev), packetList->head);
			--bufSize;
		}
	}

	return bufSize > 0;
};