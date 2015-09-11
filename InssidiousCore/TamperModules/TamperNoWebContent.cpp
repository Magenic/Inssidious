
#include "TamperNoWebContent.h"



TamperNoWebContent::TamperNoWebContent(void** ppTamperConfig)
{
	this->ppNoWebContentConfig = (TamperNoWebContentConfig**)ppTamperConfig;
}

TamperNoWebContent::~TamperNoWebContent()
{

}


short TamperNoWebContent::process(PacketList* packetList)
{

	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}

	//if ((*ppNoWebContentConfig)->something)
	//{
	//	while (packetList->head->next != packetList->tail)
	//	{
	//		packetList->freeNode(packetList->popNode(packetList->head->next));
	//	}
	//}
	//else if ((*ppNoWebContentConfig)->something)
	//{
	//	//TODO: Redirect to Portal
	//}
	

	return 0;

}

