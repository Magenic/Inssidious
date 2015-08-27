#include "TamperModule.h"

class TamperQuality : public TamperModule
{
public:
	TamperQuality(void** ppTamperConfig);
	~TamperQuality();
	short process(PacketList* packetList) override;

	short resolutionSet = 0;
	volatile short jitterVarianceInMs;


private:
	void** ppTamperConfig;

	volatile short chance = 0; // [0-10000]
	volatile short setNextCount = 0;

	const unsigned int TCP_MIN_SIZE = sizeof(WINDIVERT_IPHDR) + sizeof(WINDIVERT_TCPHDR);


	Packet jitterHeadNode = Packet{ 0 }, jitterTailNode = Packet{ 0 };
	Packet *bufHead = &jitterHeadNode, *bufTail = &jitterTailNode;
	int bufSize = 0;

	short isBufEmpty();


};

