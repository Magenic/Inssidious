
#include "TamperConditions.h"
#include <timeapi.h>


TamperConditions::TamperConditions(void** ppTamperConfig, PSLIST_HEADER packetSList)
{
	this->ppConditionsConfig = reinterpret_cast<TamperConditionsConfig**>(ppTamperConfig);
	this->packetSList = packetSList;


	/* Fill the packet tamper patterns array */

	patterns[0] = 0x64;
	patterns[1] = 0x13;
	patterns[2] = 0x88;
	patterns[3] = 0x40;
	patterns[4] = 0x1F;
	patterns[5] = 0xA0;
	patterns[6] = 0xAA;
	patterns[7] = 0x55;


	/* Set a four second timer resolution for future timeGetTime calls */

	timeBeginPeriod(timerResolution);

}


short TamperConditions::process(DivertPacket *& dPacket)
{

	if (calcChance((*ppConditionsConfig)->chanceLoss))
	{
		/* Drop this packet and return */
		
		free(dPacket);
		dPacket = nullptr;
		return 0;
	}
	else if (calcChance((*ppConditionsConfig)->chanceDelay))
	{
	
		/* Allocate memory for the packet list entry */

		PacketListEntry* pPacketListEntry = static_cast<PacketListEntry*>(_aligned_malloc(sizeof(PacketListEntry), MEMORY_ALLOCATION_ALIGNMENT));


		/* Copy the dPacket values and set the packet release time */

		memcpy(pPacketListEntry->packet, dPacket->packet, dPacket->packetLength);
		pPacketListEntry->packetLength = dPacket->packetLength;
		memcpy(&(pPacketListEntry->addr), &dPacket->addr, sizeof(WINDIVERT_ADDRESS));
		pPacketListEntry->releaseTimestamp = timeGetTime() + delayTime;


		/* Add the entry to the list */

		InterlockedPushEntrySList(packetSList, &(pPacketListEntry->ItemEntry));


		/* Drop the dPacket */

		free(dPacket);
		dPacket = nullptr;
		return 0;
	}
	else if (calcChance((*ppConditionsConfig)->chanceCorrupt))
	{
		char *data = nullptr;
		UINT dataLen = 0;

		/* Parse the packet for data */

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
				/* Tamper somewhere near the middle */
				UINT len = dataLen;
				UINT len_d4 = len / 4;
				corruptPacket(data + len / 2 - len_d4 / 2 + 1, len_d4);
			}

			/* Do not recalculate the packet checksum so the receiver knows it is bad */
			
		}
	}
	else if (dPacket->packetLength > TCP_MIN_SIZE && calcChance((*ppConditionsConfig)->chanceReset))
	{
		/* Set the TCP RESET flag on this packet */
		
		PWINDIVERT_TCPHDR pTcpHdr;
		WinDivertHelperParsePacket(dPacket->packet, dPacket->packetLength, 0, 0, 0, 0, &pTcpHdr, 0, 0, 0);

		if (pTcpHdr) /* tcp header pointer is valid */
		{
			pTcpHdr->Rst = 1;
			WinDivertHelperCalcChecksums(dPacket->packet, dPacket->packetLength, 0);
		}
	}


	return 0;
}
