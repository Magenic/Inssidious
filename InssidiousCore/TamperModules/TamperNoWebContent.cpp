
#include "TamperNoWebContent.h"



TamperNoWebContent::TamperNoWebContent(void** ppTamperConfig, PSLIST_HEADER packetSList)
{
	this->ppNoWebContentConfig = reinterpret_cast<TamperNoWebContentConfig**>(ppTamperConfig);
}


short TamperNoWebContent::process(DivertPacket *& dPacket)
{


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

