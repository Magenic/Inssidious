#include "TamperModule.h"


class TamperConditions : public TamperModule
{
public:
	TamperConditions(void** ppTamperConfig, PSLIST_HEADER packetSList);

	short process(DivertPacket *& dPacket) override;


private:

	/* UI configuration received in ppSpeedTime */

	TamperConditionsConfig** ppConditionsConfig;
	PSLIST_HEADER packetSList;

	/* Timer Resolution in milliseconds for timeGetTime calls */

	UINT timerResolution = 4;
	UINT delayTime = 700; /* 700ms delay for any delayed packets */


	/* For TCP Reset, use TCP_MIN_SIZE to quickly skip non TCP packets */

	const unsigned int TCP_MIN_SIZE = sizeof(WINDIVERT_IPHDR) + sizeof(WINDIVERT_TCPHDR);

	
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

