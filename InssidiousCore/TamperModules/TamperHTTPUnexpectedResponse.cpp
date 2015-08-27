
#include "TamperHTTPUnexpectedResponse.h"



TamperHTTPUnexpectedResponse::TamperHTTPUnexpectedResponse(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperHTTPUnexpectedResponse::~TamperHTTPUnexpectedResponse()
{

}

short TamperHTTPUnexpectedResponse::process(PacketList* packetList)
{
	return 0;
};