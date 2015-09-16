
#include "TamperWebServiceFailures.h"


TamperWebServiceFailures::TamperWebServiceFailures(void** ppTamperConfig)
{

	this->ppTamperConfig = (TamperWebServiceFailuresConfig**)ppTamperConfig;
	
}




short TamperWebServiceFailures::process(PacketList* packetList)
{
	return 0;
}
