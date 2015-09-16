#include "TamperModule.h"
#include "TamperTypes.h"

class TamperFirewall : public TamperModule
{
public:
	TamperFirewall(void** ppTamperConfig);

	short process(PacketList* packetList) override;

private:
	TamperFirewallConfig** ppFirewallConfig;

	u_short port80;
	u_short port443;
};

