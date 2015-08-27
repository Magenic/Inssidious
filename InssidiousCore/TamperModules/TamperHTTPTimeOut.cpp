
#include "TamperHTTPTimeOut.h"

#define NAME "reset"

short TamperHTTPTimeOut::process(PacketList* packetList)
{

	return 0;
}

TamperHTTPTimeOut::TamperHTTPTimeOut(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperHTTPTimeOut::~TamperHTTPTimeOut()
{
	
}
