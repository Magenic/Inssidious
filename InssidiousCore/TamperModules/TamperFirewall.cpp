
#include "TamperFirewall.h"


TamperFirewall::TamperFirewall(void** ppTamperConfig)
{
	this->ppFirewallConfig = reinterpret_cast<TamperFirewallConfig**>(ppTamperConfig);

	port80 = htons(80);
	port443 = htons(443);
}


short TamperFirewall::process(PacketList* packetList)
{

	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}


	/* Loop and drop any packets traveling over blocked ports */

	Packet *pDivertPacket = packetList->head->next;
	while (pDivertPacket != packetList->tail)
	{

		WINDIVERT_IPHDR *iphdr;
		WINDIVERT_TCPHDR *tcphdr = nullptr;
		WINDIVERT_UDPHDR *udphdr = nullptr;
		WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen, &iphdr, 0, 0, 0, &tcphdr, &udphdr, 0, 0);

		if (tcphdr)
		{
			if ((tcphdr->DstPort == port80 || tcphdr->SrcPort == port80) && (*ppFirewallConfig)->allowHTTP)
			{
				pDivertPacket = pDivertPacket->next;
				continue;
			}

			if ((tcphdr->DstPort == port443 || tcphdr->SrcPort == port443) && (*ppFirewallConfig)->allowHTTPS)
			{
				pDivertPacket = pDivertPacket->next;
				continue;
			}
		}

		if (udphdr)
		{
			if ((udphdr->DstPort == port80 || udphdr->SrcPort == port80) && (*ppFirewallConfig)->allowHTTP)
			{
				pDivertPacket = pDivertPacket->next;
				continue;
			}

			if ((udphdr->DstPort == port443 || udphdr->SrcPort == port443) && (*ppFirewallConfig)->allowHTTPS)
			{
				pDivertPacket = pDivertPacket->next;
				continue;
			}
		}


		/* Drop the packet */
		pDivertPacket = pDivertPacket->next;
		packetList->freeNode(packetList->popNode(pDivertPacket->prev));
	}


	//TODO: Content blocked
	//if ((*ppFirewallConfig)->contentBlocked)
	//{
	//	
	//}

	return 0;
}