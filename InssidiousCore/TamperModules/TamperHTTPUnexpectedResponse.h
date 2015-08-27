#include "TamperModule.h"

class TamperHTTPUnexpectedResponse : public TamperModule
{
public:
	TamperHTTPUnexpectedResponse(void** ppTamperConfig);
	~TamperHTTPUnexpectedResponse();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;
};
