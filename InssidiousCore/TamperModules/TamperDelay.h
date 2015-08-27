#include "TamperModule.h"

class TamperDelay : public TamperModule
{
public:
	TamperDelay(void** ppTamperConfig);
	~TamperDelay();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;

	volatile short chance = 1000; // [0-10000]
	short resolutionSet = 0;

	// time frame in ms, when a throttle start the packets within the time 
	// will be queued and sent altogether when time is over
	volatile short throttleFrame;

	Packet throttleHeadNode = Packet{ 0 }, throttleTailNode = Packet{ 0 };
	Packet *bufHead = &throttleHeadNode, *bufTail = &throttleTailNode;
	int bufSize = 0;
	DWORD throttleStartTick = 0;

	short isBufEmpty();

};
