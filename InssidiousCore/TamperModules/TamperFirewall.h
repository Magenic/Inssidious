#include "TamperModule.h"


class TamperFirewall : public TamperModule
{
public:
	TamperFirewall(void** ppTamperConfig, PSLIST_HEADER packetSList);

	short process(DivertPacket *& dPacket) override;

private:
	TamperFirewallConfig** ppFirewallConfig;

	std::list<unsigned short>* activePortList;
	std::list<unsigned short> customPortList;
	unsigned short customListVersion;

};

