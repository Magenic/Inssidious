#include "TamperModule.h"
#include "TamperTypes.h"

class TamperNoServer : public TamperModule
{
public:
	TamperNoServer(void** ppTamperConfig);
	~TamperNoServer();
	short process(PacketList* packetList) override;

private:
	TamperNoServerConfig** ppTamperConfig;
};

