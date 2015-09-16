#include "TamperModule.h"
#include "TamperTypes.h"

class TamperNoInternet : public TamperModule
{
public:
	TamperNoInternet(void** ppTamperConfig);

	short process(PacketList* packetList) override;

private:
	TamperNoInternetConfig** ppNoInternetConfig;
};
