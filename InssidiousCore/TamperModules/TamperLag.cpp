#include <InssidiousCore/TamperModules/TamperBase.h>


#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)

#define NAME "lag"
#define LAG_MIN "0"
#define LAG_MAX "3000"
#define KEEP_AT_MOST 2000
// send FLUSH_WHEN_FULL packets when buffer is full
#define FLUSH_WHEN_FULL 800
#define LAG_DEFAULT 50
#define TIMER_RESOLUTION 4


LagModule::LagModule()
{
	lagTime = LAG_DEFAULT;

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

LagModule::~LagModule()
{
	
}

inline short LagModule::isBufEmpty()
{
		short ret = bufHead->next == bufTail;
		if (ret) assert(bufSize == 0);
		return ret;
}

short LagModule::process(PacketList* packetList)
{
	DWORD currentTime = timeGetTime();
	Packet *pac = packetList->tail->prev;
	// pick up all packets and fill in the current time
	while (bufSize < KEEP_AT_MOST && pac != packetList->head) {
		if (true /*checkDirection(pac->addr.Direction, lagInbound, lagOutbound)*/) {
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
		if (currentTime > pac->timestamp + lagTime) {
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
};