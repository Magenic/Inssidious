
#include "TamperNoServer.h"


short TamperNoServer::process(PacketList* packetList)
{
	return 0;
}

TamperNoServer::TamperNoServer(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperNoServer::~TamperNoServer()
{
	
}
