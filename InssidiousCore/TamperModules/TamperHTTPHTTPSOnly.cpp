
#include "TamperHTTPHTTPSOnly.h"


short TamperHTTPHTTPSOnly::process(PacketList* packetList)
{
	short tampered = FALSE;
	Packet *pac = packetList->head->next;
	while (pac != packetList->tail) 
	{
		if (/*checkDirection(pac->addr.Direction, tamperInbound, tamperOutbound)*/
			/*&& */calcChance(chance)) 
		{
			WINDIVERT_TCPHDR *tcphdr = NULL;
			WINDIVERT_UDPHDR *udphdr = NULL;
			WinDivertHelperParsePacket(pac->packet, pac->packetLen, NULL, NULL, NULL, NULL, &tcphdr, &udphdr, NULL, NULL);

			if (tcphdr)
			{
				if (tcphdr->DstPort != 80 || tcphdr->DstPort != 443)
				{
					packetList->freeNode(packetList->popNode(pac));
					tampered = TRUE;
				}
			}

			if (udphdr)
			{
				if (udphdr->DstPort != 80 || udphdr->DstPort != 443)
				{
					packetList->freeNode(packetList->popNode(pac));
					tampered = TRUE;
				}
			}

		}
		pac = pac->next;
	}
	return tampered;
}

TamperHTTPHTTPSOnly::TamperHTTPHTTPSOnly(void** ppTamperConfig)
{
	this->ppTamperConfig = ppTamperConfig;
}

TamperHTTPHTTPSOnly::~TamperHTTPHTTPSOnly()
{
	
}
