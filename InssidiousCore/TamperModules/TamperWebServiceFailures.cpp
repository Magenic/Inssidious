
#include "TamperWebServiceFailures.h"


TamperWebServiceFailures::TamperWebServiceFailures(void** ppTamperConfig)
{

	this->ppTamperConfig = reinterpret_cast<TamperWebServiceFailuresConfig**>(ppTamperConfig);
	
}




short TamperWebServiceFailures::process(PacketList* packetList)
{
	return 0;
}
