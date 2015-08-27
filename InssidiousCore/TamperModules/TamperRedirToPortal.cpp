
#include "TamperRedirToPortal.h"



TamperRedirToPortal::TamperRedirToPortal(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperRedirToPortal::~TamperRedirToPortal()
{
	
}

short TamperRedirToPortal::process(PacketList* packetList)
{
	return 0;
}
