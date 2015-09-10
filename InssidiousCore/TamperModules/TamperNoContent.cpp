
#include "TamperNoContent.h"



TamperNoContent::TamperNoContent(void** ppTamperConfig)
{
	this->ppNoContentConfig = (TamperNoContentConfig**)ppTamperConfig;
}

TamperNoContent::~TamperNoContent()
{

}


short TamperNoContent::process(PacketList* packetList)
{

	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}

	//if ((*ppNoContentConfig)->something)
	//{
	//	while (packetList->head->next != packetList->tail)
	//	{
	//		packetList->freeNode(packetList->popNode(packetList->head->next));
	//	}
	//}
	//else if ((*ppNoContentConfig)->something)
	//{
	//	//TODO: Redirect to Portal
	//}
	

	return 0;

}

