
#include "TamperNoDNS.h"



short TamperNoDNS::process(PacketList* packetList)
{
	return 0;
}

TamperNoDNS::TamperNoDNS(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperNoDNS::~TamperNoDNS()
{
	
}
