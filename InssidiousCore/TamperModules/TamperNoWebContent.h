#include "TamperModule.h"
#include "TamperTypes.h"

class TamperNoWebContent : public TamperModule
{
public:
	TamperNoWebContent(void** ppTamperConfig, PSLIST_HEADER packetSList);

	short process(DivertPacket *& dPacket) override;

private:
	TamperNoWebContentConfig** ppNoWebContentConfig;
};
