#include "TamperModule.h"

class TamperRedirToPortal : public TamperModule
{
public:
	TamperRedirToPortal(void** ppTamperConfig);
	~TamperRedirToPortal();
	short process(PacketList* packetList) override;

private: 
	void** ppTamperConfig;
};
