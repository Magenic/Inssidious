#include <InssidiousCore/TamperModules/TamperBase.h>

short NoPacketsModule::process(PacketList* packetList)
{
	
	int dropped = 0;
	while (packetList->head->next != packetList->tail)
	{
		packetList->freeNode(packetList->popNode(packetList->head->next));
		++dropped;
	}

	return dropped > 0;

}

NoPacketsModule::~NoPacketsModule()
{
	
}
