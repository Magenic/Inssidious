#include "TamperModule.h"


class TamperFirewall : public TamperModule
{
public:
	TamperFirewall(void** ppTamperConfig);

	short process(PacketList* packetList) override;

private:
	TamperFirewallConfig** ppFirewallConfig;

	std::list<unsigned short>* activePortList;
	std::list<unsigned short> customPortList;
	unsigned short customListVersion;

};

