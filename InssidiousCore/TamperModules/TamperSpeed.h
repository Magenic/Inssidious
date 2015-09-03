#ifndef TAMPERSPEED_H
#define TAMPERSPEED_H

#include "TamperModule.h"
#include "TamperTypes.h"

class TamperSpeed : public TamperModule
{

public:
	TamperSpeed(void** ppTamperConfig);
	~TamperSpeed();

	short process(PacketList* packetList) override;


private:

	/* UI configuration received in ppSpeedTime */

	TamperSpeedConfig** ppTamperSpeedConfig;


	/* Timer Resolution in milliseconds for timeGetTime calls */

	UINT timerResolution = 4;


	/* Keep track of how many packets we have in the buffer */

	unsigned __int64 bufferSize = 0;
	const unsigned __int64 numMaxBufferPackets = ULLONG_MAX;


	/* Variables for a linked list to buffer packets in before re-injecting at a later time */

	Packet speedHeadNode;
	Packet speedTailNode;
	Packet* bufferHead = &speedHeadNode;
	Packet* bufferTail = &speedTailNode;


	/* Assert if we've lost track of packets somehow */

	inline short isBufEmpty()
	{
		short ret = bufferHead->next == bufferTail;
		if (ret && !(bufferSize == 0))
		{
			/* We have packets that bufSize isn't accouting for */
			DebugBreak();
		}
		return ret;
	}

};

#endif //TAMPERSPEED_H