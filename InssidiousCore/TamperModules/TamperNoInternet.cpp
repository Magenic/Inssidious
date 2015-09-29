
#include "TamperNoInternet.h"



TamperNoInternet::TamperNoInternet(void** ppTamperConfig, PSLIST_HEADER packetSList)
{
	this->ppNoInternetConfig = reinterpret_cast<TamperNoInternetConfig**>(ppTamperConfig);
}




short TamperNoInternet::process(DivertPacket *& dPacket)
{

	if ((*ppNoInternetConfig)->noInternet)
	{
		free(dPacket);
		dPacket = nullptr;
	}	

	return 0;
}

