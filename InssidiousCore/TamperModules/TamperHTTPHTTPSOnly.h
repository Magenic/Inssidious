#include "TamperModule.h"

class TamperHTTPHTTPSOnly : public TamperModule
{
public:
	TamperHTTPHTTPSOnly(void** ppTamperConfig);
	~TamperHTTPHTTPSOnly();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;
	volatile short chance = 1000; // [0 - 10000]
};

