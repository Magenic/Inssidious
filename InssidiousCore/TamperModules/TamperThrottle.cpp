#include <InssidiousCore/TamperModules/TamperBase.h>

#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)

#define NAME "throttle"
#define TIME_MIN "0"
#define TIME_MAX "1000"
#define TIME_DEFAULT 30
// threshold for how many packet to throttle at most
#define KEEP_AT_MOST 1000
#define TIMER_RESOLUTION 4

ThrottleModule::ThrottleModule()
{
	throttleFrame = TIME_DEFAULT;

	if (bufHead->next == NULL && bufTail->next == NULL) {
		bufHead->next = bufTail;
		bufTail->prev = bufHead;
		bufSize = 0;
	}
	else {
		assert(isBufEmpty());
	}
	throttleStartTick = 0;

	if (!resolutionSet) {
		// begin only fails when period out of range
		timeBeginPeriod(TIMER_RESOLUTION);
		resolutionSet = 1;
	}
	
}

inline short ThrottleModule::isBufEmpty()
{
	short ret = bufHead->next == bufTail;
	if (ret) assert(bufSize == 0);
	return ret;
}

short ThrottleModule::process(PacketList* packetList)
{
	short throttled = FALSE;

	if (!throttleStartTick) {
		if (!packetList->isListEmpty() && calcChance(chance)) {
			//LOG("Start new throttling w/ chance %.1f, time frame: %d", chance / 10.0, throttleFrame);
			throttleStartTick = timeGetTime();
			throttled = TRUE;
			goto THROTTLE_START; // need this goto since maybe we'll start and stop at this single call
		}
	}
	else {
	THROTTLE_START:
		// start a block for declaring local variables
	{
		// already throttling, keep filling up
		Packet *pac = packetList->tail->prev;
		DWORD currentTick = timeGetTime();
		while (bufSize < KEEP_AT_MOST && pac != packetList->head) {
			if (true /*checkDirection(pac->addr.Direction, throttleInbound, throttleOutbound)*/) {
				packetList->insertAfter(packetList->popNode(pac), bufHead);
				++bufSize;
				pac = packetList->tail->prev;
			}
			else {
				pac = pac->prev;
			}
		}

		// send all when throttled enough, including in current step
		if (bufSize >= KEEP_AT_MOST || (currentTick - throttleStartTick > (unsigned int)throttleFrame)) 
		{
			Packet *oldLast = packetList->tail->prev;
			//LOG("Throttled end, send all %d packets. Buffer at max: %s", bufSize, bufSize == KEEP_AT_MOST ? "YES" : "NO");
			while (!isBufEmpty())
			{
				packetList->insertAfter(packetList->popNode(bufTail->prev), oldLast);
				--bufSize;
			}
			throttleStartTick = 0;
		}
	}
	}

	return throttled;
}


ThrottleModule::~ThrottleModule()
{
	
}
