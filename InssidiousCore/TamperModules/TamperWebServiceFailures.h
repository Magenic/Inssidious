#include "TamperModule.h"
#include "TamperTypes.h"

class TamperWebServiceFailures : public TamperModule
{
public:
	TamperWebServiceFailures(void** ppTamperConfig);

	short process(PacketList* packetList) override;

private:
	TamperWebServiceFailuresConfig** ppTamperConfig;
};
