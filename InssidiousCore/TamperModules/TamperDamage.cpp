
#include "TamperDamage.h"



TamperDamage::TamperDamage(void** ppTamperConfig, PSLIST_HEADER packetSList)
{
	this->ppDamageConfig = reinterpret_cast<TamperDamageConfig**>(ppTamperConfig);

	/* Fill the packet tamper patterns array */

	patterns[0] = 0x64;
	patterns[1] = 0x13;
	patterns[2] = 0x88;
	patterns[3] = 0x40;
	patterns[4] = 0x1F;
	patterns[5] = 0xA0;
	patterns[6] = 0xAA;
	patterns[7] = 0x55;

}


short TamperDamage::process(DivertPacket *& dPacket)
{

	if (calcChance((*ppDamageConfig)->chanceDamage))
	{
		char *data = nullptr;
		UINT dataLen = 0;

		/* Parse the packet for any data */

		if (WinDivertHelperParsePacket(dPacket->packet, dPacket->packetLength, 0, 0, 0, 0, 0, 0, reinterpret_cast<PVOID*>(&data), &dataLen)
			&& data != nullptr && dataLen != 0)
		{
			/* Tamper all of a short packet */

			if (dataLen <= 4)
			{
				corruptPacket(data, dataLen);
			}
			else
			{
				/* Tamper somewhere near the middle of larger packets */

				UINT len = dataLen;
				UINT len_d4 = len / 4;
				corruptPacket(data + len / 2 - len_d4 / 2 + 1, len_d4);
			}


			/* Recalculate the packet checksum so the receiver doesn't know it is bad */

			WinDivertHelperCalcChecksums(dPacket->packet, dPacket->packetLength, WINDIVERT_HELPER_NO_IP_CHECKSUM);
			
		}
	}
	else if (calcChance((*ppDamageConfig)->chanceClose))
	{
		WINDIVERT_IPHDR *iphdr;
		WINDIVERT_TCPHDR *tcphdr = nullptr;

		WinDivertHelperParsePacket(dPacket->packet, dPacket->packetLength, &iphdr, 0, 0, 0, &tcphdr, 0, 0, 0);

		if (iphdr)
		{
			if (tcphdr)
			{
				/* Set the fin & ack flags to signal to close the connection */

				tcphdr->Fin = 1;
				tcphdr->Ack = 1;
				WinDivertHelperCalcChecksums(dPacket->packet, dPacket->packetLength, WINDIVERT_HELPER_NO_IP_CHECKSUM);
			}
		}

	}

	return 0;

}

