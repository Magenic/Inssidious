#ifndef TAMPERSPEED_H
#define TAMPERSPEED_H

#include "TamperModule.h"
#include "TamperTypes.h"

class TamperSpeed : public TamperModule
{

public:
	TamperSpeed(void** ppTamperConfig, PSLIST_HEADER packetSList);

	short process(DivertPacket *& dPacket) override;


private:

	/* UI configuration received in ppSpeedTime */

	TamperSpeedConfig** ppTamperSpeedConfig;
	PSLIST_HEADER packetSList;


	DWORD lastReleaseTime = 0;

};

#endif //TAMPERSPEED_H