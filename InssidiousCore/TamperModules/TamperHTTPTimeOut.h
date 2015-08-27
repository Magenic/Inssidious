#include "TamperModule.h"

class TamperHTTPTimeOut : public TamperModule
{
public:
	TamperHTTPTimeOut(void** ppTamperConfig);
	~TamperHTTPTimeOut();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;
};
