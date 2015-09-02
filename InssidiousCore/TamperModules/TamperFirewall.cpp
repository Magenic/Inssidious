
#include "TamperFirewall.h"


TamperFirewall::TamperFirewall(void** ppTamperConfig)
{
	this->ppFirewallConfig = (TamperFirewallConfig**)ppTamperConfig;
}

TamperFirewall::~TamperFirewall()
{

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
		WINDIVERT_TCPHDR *tcphdr = NULL;
		WINDIVERT_UDPHDR *udphdr = NULL;
		WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen, 0, 0, 0, 0, &tcphdr, &udphdr, 0, 0);

		if (tcphdr)
		{
			if (tcphdr->DstPort == 80 && (*ppFirewallConfig)->allowHTTP)
			{
				pDivertPacket = pDivertPacket->next;
				continue;
			}

			if (tcphdr->DstPort == 443 && (*ppFirewallConfig)->allowHTTPS)
			{
				pDivertPacket = pDivertPacket->next;
				continue;
			}
		}

		if (udphdr)
		{
			if (udphdr->DstPort == 80 && (*ppFirewallConfig)->allowHTTP)
			{
				pDivertPacket = pDivertPacket->next;
				continue;
			}

			if (udphdr->DstPort == 443 && (*ppFirewallConfig)->allowHTTPS)
			{
				pDivertPacket = pDivertPacket->next;
				continue;
			}
		}


		/* Drop the packet */

		packetList->freeNode(packetList->popNode(pDivertPacket));
	}


	//TODO: Content blocked
	//if ((*ppFirewallConfig)->contentBlocked)
	//{
	//	
	//}

	return 0;
}