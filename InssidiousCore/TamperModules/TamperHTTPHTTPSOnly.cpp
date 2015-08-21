#include <InssidiousCore/TamperModules/TamperBase.h>

short HTTPHTTPSOnlyModule::process(PacketList* packetList)
{
	short tampered = FALSE;
	Packet *pac = packetList->head->next;
	while (pac != packetList->tail) {
		if (/*checkDirection(pac->addr.Direction, tamperInbound, tamperOutbound)*/
			/*&& */calcChance(chance)) 
		{
			WINDIVERT_TCPHDR *tcphdr = NULL;
			WINDIVERT_UDPHDR *udphdr = NULL;
			if (WinDivertHelperParsePacket(pac->packet, pac->packetLen, NULL, NULL, NULL,
				NULL, &tcphdr, &udphdr, NULL, NULL)) 
			{
				if (tcphdr)
				{
					if (tcphdr->DstPort != 80 || tcphdr->DstPort != 443)
					{
						packetList->freeNode(packetList->popNode(pac));
					}
				}
				if (udphdr)
				{
					if (udphdr->DstPort != 80 || udphdr->DstPort != 443)
					{
						packetList->freeNode(packetList->popNode(pac));
					}
				}

				tampered = TRUE;
			}
			else
			{
				if (tcphdr)
				{
					int i = 0;
				}
			}
		}
		pac = pac->next;
	}
	return tampered;
}

HTTPHTTPSOnlyModule::~HTTPHTTPSOnlyModule()
{
	
}
