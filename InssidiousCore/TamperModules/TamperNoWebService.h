#include "TamperModule.h"
#include "TamperTypes.h"

class TamperNoWebService : public TamperModule
{
public:
	TamperNoWebService(void** ppTamperConfig);
	~TamperNoWebService();
	short process(PacketList* packetList) override;

private:
	TamperNoWebServiceConfig** ppTamperConfig;
};
