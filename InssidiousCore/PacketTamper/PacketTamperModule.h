#include "PacketList.h"

class PacketTamperModule
{

public:

	//void(*startUp)(); // called when starting up the module
	//void(*closeDown)(PacketList::PacketNode *head, PacketList::PacketNode *tail); // called when starting up the module
	short process(PacketList* packetList);

	volatile short enabledFlag; // volatile short flag to determine enabled or not


};