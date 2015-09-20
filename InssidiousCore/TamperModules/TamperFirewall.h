#include "TamperModule.h"
#include "TamperTypes.h"
#include <list>

class TamperFirewall : public TamperModule
{
public:
	TamperFirewall(void** ppTamperConfig);

	short process(PacketList* packetList) override;

private:
	TamperFirewallConfig** ppFirewallConfig;

	std::list<u_short>* activePortList;
	std::list<u_short> customPortList;
	u_short customListVersion;

};

