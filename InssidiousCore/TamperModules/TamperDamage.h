#include "TamperModule.h"
#include "TamperTypes.h"

class TamperDamage : public TamperModule
{
public:
	TamperDamage(void** ppTamperConfig);

	short process(PacketList* packetList) override;

private:
	TamperDamageConfig** ppDamageConfig;
};
