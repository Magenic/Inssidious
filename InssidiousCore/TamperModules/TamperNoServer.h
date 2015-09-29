#include "TamperModule.h"
#include "TamperTypes.h"

class TamperNoServer : public TamperModule
{
public:
	TamperNoServer(void** ppTamperConfig, PSLIST_HEADER packetSList);

	short process(DivertPacket *& dPacket) override;

private:
	TamperNoServerConfig** ppNoServerConfig;

	std::list<UINT32> serverList;
	UINT32 serverListVersion;
};

