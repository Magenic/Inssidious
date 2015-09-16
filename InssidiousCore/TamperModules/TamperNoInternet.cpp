
#include "TamperNoInternet.h"



TamperNoInternet::TamperNoInternet(void** ppTamperConfig)
{
	this->ppNoInternetConfig = reinterpret_cast<TamperNoInternetConfig**>(ppTamperConfig);
}




short TamperNoInternet::process(PacketList* packetList)
{

	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}

	if ((*ppNoInternetConfig)->localNetwork)
	{
		while (packetList->head->next != packetList->tail)
		{
			packetList->freeNode(packetList->popNode(packetList->head->next));
		}
	}
	else if ((*ppNoInternetConfig)->redirToPortal)
	{
		//TODO: Redirect to Portal
	}
	

	return 0;

}

