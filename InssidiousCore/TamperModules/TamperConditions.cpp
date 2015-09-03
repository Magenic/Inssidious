
#include "TamperConditions.h"


TamperConditions::TamperConditions(void** ppTamperConfig)
{
	this->ppConditionsConfig = (TamperConditionsConfig**)ppTamperConfig;
	
	
	/* Start a linked list to buffer packets in before re-injecting at a later time */

	this->conditionsHeadNode = Packet{ 0 };
	this->conditionsTailNode = Packet{ 0 };
	bufferHead->next = bufferTail;
	bufferTail->prev = bufferHead;
	bufferSize = 0;


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


TamperConditions::~TamperConditions()
{

}


short TamperConditions::process(PacketList* packetList)
{

	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}

	/* Loop through all packets in the list */

	Packet* pDivertPacket = packetList->head->next;
	while (pDivertPacket != packetList->tail)
	{
		if (calcChance((*ppConditionsConfig)->chanceLoss))
		{
			/* Drop this packet */
			pDivertPacket = pDivertPacket->next;
			packetList->freeNode(packetList->popNode(pDivertPacket->prev));
		}
		else if (calcChance((*ppConditionsConfig)->chanceDelay))
		{
			/* Pull this packet into the delay buffer */
			pDivertPacket = pDivertPacket->next;
			packetList->insertAfter(packetList->popNode(pDivertPacket->prev), bufferHead)->timestamp = timeGetTime() + delayTime;
			

			/* Increment the buffer size and the next packet's release time */

			++bufferSize;
		}
		else if (calcChance((*ppConditionsConfig)->chanceCorrupt))
		{
			char *data = nullptr;
			UINT dataLen = 0;

			/* Parse the packet for any data */

			if (WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen, 0, 0, 0, 0, 0, 0, (PVOID*)&data, &dataLen)
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

				//Perhaps offer the evil version, recalculating this, this one day
				//WinDivertHelperCalcChecksums(pDivertPacket->packet, pDivertPacket->packetLen, 0);
				
				pDivertPacket = pDivertPacket->next;
			}
		}
		else if (pDivertPacket->packetLen > TCP_MIN_SIZE && calcChance((*ppConditionsConfig)->chanceReset))
		{
			/* Set the TCP RESET flag on this packet */
			
			PWINDIVERT_TCPHDR pTcpHdr;
			WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen,	0, 0, 0, 0,	&pTcpHdr, 0, 0, 0);

			if (pTcpHdr) /* tcp header pointer is valid */
			{
				pTcpHdr->Rst = 1;
				WinDivertHelperCalcChecksums(pDivertPacket->packet, pDivertPacket->packetLen, 0);
			}

			pDivertPacket = pDivertPacket->next;
		}
		else
		{
			/* This packet survives */

			pDivertPacket = pDivertPacket->next;
		}
	}


	/* Send any packets that are overdue to go out from the delay chance */

	DWORD currentTime = timeGetTime();
	while (!isBufEmpty())
	{
		if (currentTime > bufferTail->prev->timestamp)
		{
			packetList->insertAfter(packetList->popNode(bufferTail->prev), packetList->head);
			--bufferSize;
		}
	}


	return 0;

}
