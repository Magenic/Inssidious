
#include "TamperNoInternet.h"



short TamperNoInternet::process(PacketList* packetList)
{
	
	int dropped = 0;
	while (packetList->head->next != packetList->tail)
	{
		packetList->freeNode(packetList->popNode(packetList->head->next));
		++dropped;
	}

	return dropped > 0;

}

TamperNoInternet::TamperNoInternet(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperNoInternet::~TamperNoInternet()
{
	
}
