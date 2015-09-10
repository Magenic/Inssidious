#include "TamperModule.h"
#include "TamperTypes.h"

class TamperSecurity : public TamperModule
{
public:
	TamperSecurity(void** ppTamperConfig);
	~TamperSecurity();
	short process(PacketList* packetList) override;

private:
	TamperSecurityConfig** ppSecurityConfig;
};
