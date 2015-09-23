
#include "TamperDamage.h"



TamperDamage::TamperDamage(void** ppTamperConfig)
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


short TamperDamage::process(PacketList* packetList)
{

	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}


	Packet* pDivertPacket = packetList->head->next;
	while (pDivertPacket != packetList->tail)
	{
		if (calcChance((*ppDamageConfig)->chanceDamage))
		{
			char *data = nullptr;
			UINT dataLen = 0;

			/* Parse the packet for any data */

			if (WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen, 0, 0, 0, 0, 0, 0, reinterpret_cast<PVOID*>(&data), &dataLen)
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

				WinDivertHelperCalcChecksums(pDivertPacket->packet, pDivertPacket->packetLen, WINDIVERT_HELPER_NO_IP_CHECKSUM);
				pDivertPacket = pDivertPacket->next;
			}
			else
			{
				/* No packet data or a problem parsing it. Skip this packet */

				pDivertPacket = pDivertPacket->next;
			}
		}
		//else if ((*ppDamageConfig)->something)
		//{
		//	//TODO: Redirect to Portal
		//}
		else
		{
			/* This packet survives */

			pDivertPacket = pDivertPacket->next;
		}
	}



	return 0;

}

