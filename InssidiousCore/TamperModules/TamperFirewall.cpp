
#include "TamperFirewall.h"


TamperFirewall::TamperFirewall(void** ppTamperConfig)
{
	this->ppFirewallConfig = reinterpret_cast<TamperFirewallConfig**>(ppTamperConfig);

	privateListHead = static_cast<PSLIST_HEADER>(_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT));
	InitializeSListHead(privateListHead);
	privateListVersion = 0;

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

	/* Check for new custom port rules */

	while (true)
	{
		TamperFirewallEntry* listEntry = reinterpret_cast<TamperFirewallEntry*>(InterlockedPopEntrySList((*ppFirewallConfig)->customPortList));
		if (listEntry == nullptr)
		{
			/* No more items */
			break;
		}

		if (listEntry->version != privateListVersion)
		{
			/* We have old data, flush the private list and start over */

			PSLIST_ENTRY staleItems = InterlockedFlushSList(static_cast<TamperFirewallConfig*>(*ppFirewallConfig)->customPortList);

			while (staleItems != nullptr)
			{
				//Free the memory by traversing Next pointers?
				//InterlockedPopEntrySList()
				break;
			}

			privateListVersion = listEntry->version;
		}


		/* Add the new port to the list */

		InterlockedPushEntrySList(privateListHead, reinterpret_cast<PSLIST_ENTRY>(listEntry));

		/* Loop continues until we get a null pop entry */
	}


	/* Loop and drop any packets traveling over blocked ports */

	Packet *pDivertPacket = packetList->head->next;
	while (pDivertPacket != packetList->tail)
	{
		return 0;
		WINDIVERT_IPHDR *iphdr;
		WINDIVERT_TCPHDR *tcphdr = nullptr;
		WINDIVERT_UDPHDR *udphdr = nullptr;
		WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen, &iphdr, 0, 0, 0, &tcphdr, &udphdr, 0, 0);

		switch ((*ppFirewallConfig)->firewallType)
		{
		case FIREWALL_EMAIL:
			break;
		case FIREWALL_UDP:
			break;
		case FIREWALL_VPN:
			break;
		case FIREWALL_CUSTOM:
			break;
		case FIREWALL_OFF:
		default:
			return 0;
		}
		//if (tcphdr)
		//{
		//	if ((tcphdr->DstPort == port80 || tcphdr->SrcPort == port80) && (*ppFirewallConfig)->allowHTTP)
		//	{
		//		pDivertPacket = pDivertPacket->next;
		//		continue;
		//	}

		//	if ((tcphdr->DstPort == port443 || tcphdr->SrcPort == port443) && (*ppFirewallConfig)->allowHTTPS)
		//	{
		//		pDivertPacket = pDivertPacket->next;
		//		continue;
		//	}
		//}

		//if (udphdr)
		//{
		//	if ((udphdr->DstPort == port80 || udphdr->SrcPort == port80) && (*ppFirewallConfig)->allowHTTP)
		//	{
		//		pDivertPacket = pDivertPacket->next;
		//		continue;
		//	}

		//	if ((udphdr->DstPort == port443 || udphdr->SrcPort == port443) && (*ppFirewallConfig)->allowHTTPS)
		//	{
		//		pDivertPacket = pDivertPacket->next;
		//		continue;
		//	}
		//}
		///* Drop the packet */
		//pDivertPacket = pDivertPacket->next;
		//packetList->freeNode(packetList->popNode(pDivertPacket->prev));
	}

	return 0;
}