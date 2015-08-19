
#include "PacketTamperModule.h"

short PacketTamperModule::process(PacketList* packetList) 
{
	int dropped = 0;
	Packet* dropHead = packetList->head;
	while (dropHead->next != packetList->tail) {
		Packet *pac = dropHead->next;
		// chance in range of [0, 10000]
		if (enabledFlag) 
		{
			//LOG("dropped with chance %.1f%%, direction %s", chance / 100.0, BOUND_TEXT(pac->addr.Direction));
			packetList->freeNode(packetList->popNode(pac));
			++dropped;
		}
		else {
			dropHead = dropHead->next;
		}
	}

	return dropped > 0;
}