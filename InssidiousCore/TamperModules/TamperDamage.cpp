
#include "TamperDamage.h"



TamperDamage::TamperDamage(void** ppTamperConfig)
{
	this->ppDamageConfig = (TamperDamageConfig**)ppTamperConfig;
}


short TamperDamage::process(PacketList* packetList)
{

	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}

	//if ((*ppDamageConfig)->something)
	//{
	//	while (packetList->head->next != packetList->tail)
	//	{
	//		packetList->freeNode(packetList->popNode(packetList->head->next));
	//	}
	//}
	//else if ((*ppDamageConfig)->something)
	//{
	//	//TODO: Redirect to Portal
	//}
	

	return 0;

}

