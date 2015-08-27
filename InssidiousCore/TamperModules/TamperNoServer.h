#include "TamperModule.h"

class TamperNoServer : public TamperModule
{
public:
	TamperNoServer(void** ppTamperConfig);
	~TamperNoServer();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;
};

