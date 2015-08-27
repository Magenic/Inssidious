#include "TamperModule.h"

class TamperHTTPCorruptedResponse : public TamperModule
{
public:
	TamperHTTPCorruptedResponse(void** ppTamperConfig);
	~TamperHTTPCorruptedResponse();
	short process(PacketList* packetList) override;

private:
	void** ppTamperConfig;

	volatile short chance = 1000; // [0 - 10000]
	volatile short doChecksum = 1; // recompute checksum after after tampering

	// patterns covers every bit
	char patterns[8];
	int patIx = 0; // put this here to give a more random results

	inline void tamper_buf(char* buf, UINT len);
};
