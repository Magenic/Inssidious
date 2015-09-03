#include "TamperModule.h"
#include "TamperTypes.h"

class TamperConditions : public TamperModule
{
public:
	TamperConditions(void** ppTamperConfig);
	~TamperConditions();
	short process(PacketList* packetList) override;


private:

	/* UI configuration received in ppSpeedTime */

	TamperConditionsConfig** ppConditionsConfig;


	/* Timer Resolution in milliseconds for timeGetTime calls */

	UINT timerResolution = 4;
	UINT delayTime = 700; /* 700ms delay for any delayed packets */

	/* Keep track of how many packets we have in the buffer */

	unsigned __int64 bufferSize = 0;
	const unsigned __int64 numMaxBufferPackets = ULLONG_MAX;


	/* Variables for a linked list to buffer packets in before re-injecting at a later time */

	Packet conditionsHeadNode;
	Packet conditionsTailNode;
	Packet* bufferHead = &conditionsHeadNode;
	Packet* bufferTail = &conditionsTailNode;


	/* For TCP Reset, use TCP_MIN_SIZE to quickly skip non TCP packets */

	const unsigned int TCP_MIN_SIZE = sizeof(WINDIVERT_IPHDR) + sizeof(WINDIVERT_TCPHDR);


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

	
	/* Variables and function to corrupt packet data with */

	int movingPatternInt = 0;
	char patterns[8]; /* initialized in constructor */

	inline void corruptPacket(char* buf, UINT len)
	{
		UINT ix;
		for (ix = 0; ix < len; ++ix) 
		{
			buf[ix] ^= patterns[movingPatternInt++ & 0x7];
		}
	}

};

