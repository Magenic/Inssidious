#include "TamperModule.h"


class TamperContentBlocked : public TamperModule
{
public:
	TamperContentBlocked(void** ppTamperConfig);
	~TamperContentBlocked();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;
};
