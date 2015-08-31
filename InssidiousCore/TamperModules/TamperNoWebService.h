#include "TamperModule.h"

class TamperNoWebService : public TamperModule
{
public:
	TamperNoWebService(void** ppTamperConfig);
	~TamperNoWebService();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;
};
