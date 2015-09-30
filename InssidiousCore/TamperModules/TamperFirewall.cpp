
#include "TamperFirewall.h"
#include "winsock2.h"

TamperFirewall::TamperFirewall(void** ppTamperConfig, PSLIST_HEADER packetSList)
{
	this->ppFirewallConfig = reinterpret_cast<TamperFirewallConfig**>(ppTamperConfig);

	activePortList = nullptr;
	customListVersion = 0;
	customPortList.clear();

}


short TamperFirewall::process(DivertPacket *& dPacket)
{

	/* Check the port rules */

	switch ((*ppFirewallConfig)->firewallType)
	{
	case FIREWALL_EMAIL:
		activePortList = &emailPortList;
		break;
	case FIREWALL_UDP:
		activePortList = nullptr;
		break;
	case FIREWALL_VPN:
		activePortList = &vpnPortList;
		break;
	case FIREWALL_CUSTOM:
	{
		activePortList = &customPortList;
		while (true)
		{
			/* Pull an entry off of the list */

			TamperFirewallEntry* listEntry = reinterpret_cast<TamperFirewallEntry*>(InterlockedPopEntrySList((*ppFirewallConfig)->customPortList));


			/* If it is null, we've reached the end of the list and should leave the loop */

			if (listEntry == nullptr)
			{
				break;
			}


			/* If our version doesn't match the entry version, we have old data and need to clear our list */

			if (customListVersion != listEntry->version)
			{
				customPortList.clear();
				customListVersion = listEntry->version;
			}


			/* Add the port to the list and then free the list entry memory */

			customPortList.push_back(reinterpret_cast<TamperFirewallEntry*>(listEntry)->portNumber);
			_aligned_free(listEntry);
			listEntry = nullptr;


			/* Loop continues until we get a null pop entry */
		}

		break;
	}
	case FIREWALL_OFF:
	default:
		return 0;
	}



	/* Drop any packets traveling over blocked ports */

	WINDIVERT_IPHDR *iphdr;
	WINDIVERT_TCPHDR *tcphdr = nullptr;
	WINDIVERT_UDPHDR *udphdr = nullptr;
	WinDivertHelperParsePacket(dPacket->packet, dPacket->packetLength, &iphdr, 0, 0, 0, &tcphdr, &udphdr, 0, 0);

	if (!activePortList)
	{
		/* Block UDP is enabled. Drop any UDP packets */

		if (udphdr)
		{
			/* Drop packet */

			free(dPacket);
			dPacket = nullptr;
		}

		return 0;
	}


	/* Block Email, VPN, or Custom is enabled. Drop packets travelling over blocked ports */

	if (tcphdr)
	{
		for (u_short port : *activePortList)
		{
			if (tcphdr->DstPort == port || tcphdr->SrcPort == port)
			{
				/* Drop packet */

				free(dPacket);
				dPacket = nullptr;
				break;
			}
		}

		return 0;
	}
	else if (udphdr)
	{
		for (u_short port : *activePortList)
		{
			if (udphdr->DstPort == port || udphdr->SrcPort == port)
			{
				/* Drop packet */
				
				free(dPacket);
				dPacket = nullptr;
				break;
			}
		}

		return 0;
	}


	/* No TCP or UDP header. Skip this packet */

	return 0;
}