#include "TamperModule.h"
#include "TamperTypes.h"

class TamperNoInternet : public TamperModule
{
public:
	TamperNoInternet(void** ppTamperConfig, PSLIST_HEADER packetSList);

	short process(DivertPacket *& dPacket) override;

private:
	TamperNoInternetConfig** ppNoInternetConfig;
};
