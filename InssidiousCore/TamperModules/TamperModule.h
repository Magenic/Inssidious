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
		return (chance == 100) || ((rand() % 100) < chance);
	}


	static TamperModule* makeTamperModule(int tamperType, void**);

};

#endif //TAMPERMODULE_H