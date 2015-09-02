
#include "TamperNoWebService.h"


TamperNoWebService::TamperNoWebService(void** ppTamperConfig)
{

	this->ppTamperConfig = (TamperNoWebServiceConfig**)ppTamperConfig;

}

TamperNoWebService::~TamperNoWebService()
{
	
}


short TamperNoWebService::process(PacketList* packetList)
{
	return 0;
}
