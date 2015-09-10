
#include "TamperSecurity.h"



TamperSecurity::TamperSecurity(void** ppTamperConfig)
{
	this->ppSecurityConfig = (TamperSecurityConfig**)ppTamperConfig;
}

TamperSecurity::~TamperSecurity()
{

}


short TamperSecurity::process(PacketList* packetList)
{

	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}

	//if ((*ppSecurityConfig)->something)
	//{
	//	while (packetList->head->next != packetList->tail)
	//	{
	//		packetList->freeNode(packetList->popNode(packetList->head->next));
	//	}
	//}
	//else if ((*ppSecurityConfig)->something)
	//{
	//	//TODO: Redirect to Portal
	//}
	

	return 0;

}

