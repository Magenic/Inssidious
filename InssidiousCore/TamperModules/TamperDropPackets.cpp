#include <InssidiousCore/TamperModules/TamperBase.h>

short DropPacketsModule::process(PacketList* packetList)
{
	Packet* dropHead = packetList->head;

	int dropped = 0;
	while (dropHead->next != packetList->tail) 
	{
        // chance in range of [0, 10000]
        if (/*checkDirection(pac->addr.Direction, dropInbound, dropOutbound) && */ calcChance(chance)) 
		{
            //LOG("dropped with chance %.1f%%, direction %s",
            //    chance/100.0, BOUND_TEXT(pac->addr.Direction));
			packetList->freeNode(packetList->popNode(dropHead));
            ++dropped;
        } 
		else 
		{
			dropHead = packetList->head->next;
        }
    }

    return dropped > 0;

}


DropPacketsModule::~DropPacketsModule()
{
	
}
