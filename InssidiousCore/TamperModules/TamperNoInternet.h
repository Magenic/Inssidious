#include "TamperModule.h"
#include "TamperTypes.h"

class TamperNoInternet : public TamperModule
{
public:
	TamperNoInternet(void** ppTamperConfig);
	~TamperNoInternet();
	short process(PacketList* packetList) override;

private:
	TamperNoInternetConfig** ppNoInternetConfig;
};
