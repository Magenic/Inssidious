#include "TamperModule.h"
#include "TamperTypes.h"

class TamperWebServiceFailures : public TamperModule
{
public:
	TamperWebServiceFailures(void** ppTamperConfig, PSLIST_HEADER packetSList);

	short process(DivertPacket *& dPacket) override;

private:
	TamperWebServiceFailuresConfig** ppTamperConfig;
};
