
#include "TamperWebServiceFailures.h"


TamperWebServiceFailures::TamperWebServiceFailures(void** ppTamperConfig)
{

	this->ppTamperConfig = (TamperWebServiceFailuresConfig**)ppTamperConfig;

}

TamperWebServiceFailures::~TamperWebServiceFailures()
{
	
}


short TamperWebServiceFailures::process(PacketList* packetList)
{
	return 0;
}
