
#include "TamperContentBlocked.h"

short TamperContentBlocked::process(PacketList* packetList)
{
	return 0;
}

TamperContentBlocked::TamperContentBlocked(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperContentBlocked::~TamperContentBlocked()
{
	
}
