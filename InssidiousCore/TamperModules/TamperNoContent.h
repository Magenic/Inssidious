#include "TamperModule.h"
#include "TamperTypes.h"

class TamperNoContent : public TamperModule
{
public:
	TamperNoContent(void** ppTamperConfig);
	~TamperNoContent();
	short process(PacketList* packetList) override;

private:
	TamperNoContentConfig** ppNoContentConfig;
};
