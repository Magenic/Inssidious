#ifndef TAMPERMODULE_H
#define TAMPERMODULE_H

#include "TamperTypes.h"

class TamperModule
{

public:
	virtual short process(DivertPacket *& dPacket) = 0;
	virtual ~TamperModule() {}

	short calcChance(short chance)
	{
		return (chance == 100) || ((rand() % 100) < chance / 2);
	}


	static TamperModule* makeTamperModule(int tamperType, void**, PSLIST_HEADER packetSList);

};

#endif //TAMPERMODULE_H