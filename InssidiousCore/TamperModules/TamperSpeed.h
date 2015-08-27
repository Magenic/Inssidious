
#include "TamperModule.h"

class TamperSpeed : public TamperModule
{

public:
	TamperSpeed(void** ppTamperConfig);
	~TamperSpeed();
	short process(PacketList* packetList) override;


private:
	short isBufEmpty();
	int bufSize = 0;

	short** ppSpeedTime;

	short resolutionSet = 0;

	Packet speedHeadNode = Packet{ 0 }, speedTailNode = Packet{ 0 };
	Packet *bufHead = &speedHeadNode, *bufTail = &speedTailNode;
	

	

};

