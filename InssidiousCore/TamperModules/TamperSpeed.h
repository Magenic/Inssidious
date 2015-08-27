
#include "TamperModule.h"

class TamperSpeed : public TamperModule
{

public:
	TamperSpeed(void** ppTamperConfig);
	~TamperSpeed();
	short process(PacketList* packetList) override;

	volatile short lagTime;

private:
	void** ppTamperConfig;

	short resolutionSet = 0;
	Packet lagHeadNode = Packet{ 0 }, lagTailNode = Packet{ 0 };
	Packet *bufHead = &lagHeadNode, *bufTail = &lagTailNode;
	int bufSize = 0;

	short isBufEmpty();

};

