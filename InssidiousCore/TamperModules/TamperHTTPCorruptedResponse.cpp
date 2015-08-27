
#include "TamperHTTPCorruptedResponse.h"


TamperHTTPCorruptedResponse::TamperHTTPCorruptedResponse(void** ppTamperConfig)
{
	patterns[0] = 0x64;
	patterns[1] = 0x13;
	patterns[2] = 0x88;

	patterns[3] = 0x40;
	patterns[4] = 0x1F;
	patterns[5] = 0xA0;

	patterns[6] = 0xAA;
	patterns[7] = 0x55;
}

inline void TamperHTTPCorruptedResponse::tamper_buf(char* buf, UINT len)
{
	UINT ix;
	for (ix = 0; ix < len; ++ix) {
		buf[ix] ^= patterns[patIx++ & 0x7];
	}
}

short TamperHTTPCorruptedResponse::process(PacketList* packetList)
{
	short tampered = FALSE;
	Packet *pac = packetList->head->next;
	while (pac != packetList->tail) {
		if (/*checkDirection(pac->addr.Direction, tamperInbound, tamperOutbound)*/
			/*&& */calcChance(chance)) {
			char *data = NULL;
			UINT dataLen = 0;
			if (WinDivertHelperParsePacket(pac->packet, pac->packetLen, NULL, NULL, NULL,
				NULL, NULL, NULL, (PVOID*)&data, &dataLen)
				&& data != NULL && dataLen != 0) {
				// try to tamper the central part of the packet,
				// since common packets put their checksum at head or tail
				if (dataLen <= 4) {
					// for short packet just tamper it all
					tamper_buf(data, dataLen);
					//LOG("tampered w/ chance %.1f, dochecksum: %d, short packet changed all", chance / 100.0, doChecksum);
				}
				else {
					// for longer ones process 1/4 of the lens start somewhere in the middle
					UINT len = dataLen;
					UINT len_d4 = len / 4;
					tamper_buf(data + len / 2 - len_d4 / 2 + 1, len_d4);
					//LOG("tampered w/ chance %.1f, dochecksum: %d, changing %d bytes out of %u", chance / 100.0, doChecksum, len_d4, len);
				}
				// FIXME checksum seems to have some problem
				if (doChecksum) {
					WinDivertHelperCalcChecksums(pac->packet, pac->packetLen, 0);
				}
				tampered = TRUE;
			}

		}
		pac = pac->next;
	}
	return tampered;
}


TamperHTTPCorruptedResponse::~TamperHTTPCorruptedResponse()
{
	this->ppTamperConfig = ppTamperConfig;
}
