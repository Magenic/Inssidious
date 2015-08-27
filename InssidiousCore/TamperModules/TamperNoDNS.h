#include "TamperModule.h"

class TamperNoDNS : public TamperModule
{
public:
	TamperNoDNS(void** ppTamperConfig);
	~TamperNoDNS();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;
};
