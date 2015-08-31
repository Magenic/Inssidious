#include "TamperModule.h"

class TamperFirewall : public TamperModule
{
public:
	TamperFirewall(void** ppTamperConfig);
	~TamperFirewall();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;
	volatile short chance = 1000; // [0 - 10000]
};

