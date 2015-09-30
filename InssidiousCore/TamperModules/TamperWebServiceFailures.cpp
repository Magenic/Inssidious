
#include "TamperWebServiceFailures.h"


TamperWebServiceFailures::TamperWebServiceFailures(void** ppTamperConfig, PSLIST_HEADER packetSList)
{

	this->ppTamperConfig = reinterpret_cast<TamperWebServiceFailuresConfig**>(ppTamperConfig);
	
}




short TamperWebServiceFailures::process(DivertPacket *& dPacket)
{
	return 0;
}
