#ifndef TAMPERMODULE_H
#define TAMPERMODULE_H


#include "PacketList.h"

class TamperModule
{

public:
	virtual short process(PacketList* packetList) = 0;
	virtual ~TamperModule() {}

	short calcChance(short chance)
	{
		// notice that here we made a copy of chance, so even though it's volatile it is still ok
		return (chance == 10000) || ((rand() % 10000) < chance);
	}


	static TamperModule* makeTamperModule(int tamperType, void**);

};

#endif //TAMPERMODULE_H