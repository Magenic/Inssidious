#include "TamperModule.h"
#include "TamperTypes.h"

class TamperDamage : public TamperModule
{
public:
	TamperDamage(void** ppTamperConfig, PSLIST_HEADER packetSList);

	short process(DivertPacket *& dPacket) override;

private:
	TamperDamageConfig** ppDamageConfig;


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
