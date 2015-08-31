
#include "TamperNoWebService.h"



short TamperNoWebService::process(PacketList* packetList)
{
	return 0;
}

TamperNoWebService::TamperNoWebService(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperNoWebService::~TamperNoWebService()
{
	
}
