
#include "TamperNoServer.h"

TamperNoServer::TamperNoServer(void** ppTamperConfig, PSLIST_HEADER packetSList)
{
	this->ppNoServerConfig = reinterpret_cast<TamperNoServerConfig**>(ppTamperConfig);
	serverListVersion = 0;
	serverList.clear();
}

short TamperNoServer::process(DivertPacket *& dPacket)
{

	/* Check the server rules */

	switch ((*ppNoServerConfig)->noServersType)
	{
	case NO_SERVERS_CUSTOM:
	{
		while (true)
		{
			/* Pull an entry off of the list */

			TamperNoServerEntry* listEntry = reinterpret_cast<TamperNoServerEntry*>(InterlockedPopEntrySList((*ppNoServerConfig)->noServersList));


			/* If it is null, we've reached the end of the list and should leave the loop */

			if (listEntry == nullptr)
			{
				break;
			}


			/* If our version doesn't match the entry version, we have old data and need to clear our list */

			if (serverListVersion != listEntry->version)
			{
				serverList.clear();
				serverListVersion = listEntry->version;
			}


			/* Add the port to the list and then free the list entry memory */

			serverList.push_back(reinterpret_cast<TamperNoServerEntry*>(listEntry)->server);
			_aligned_free(listEntry);
			listEntry = nullptr;


			/* Loop continues until we get a null pop entry */
		}

		break;
	}
	case NO_SERVERS_OFF:
	default:
		return 0;
	}



	/* Drop any packets traveling over blocked ports */

	WINDIVERT_IPHDR *iphdr = nullptr;
	WINDIVERT_TCPHDR *tcphdr = nullptr;
	WINDIVERT_UDPHDR *udphdr = nullptr;
	WinDivertHelperParsePacket(dPacket->packet, dPacket->packetLength, &iphdr, 0, 0, 0, &tcphdr, &udphdr, 0, 0);

	if (iphdr)
	{
		for (UINT32 server : serverList)
		{
			if (iphdr->DstAddr == server || iphdr->SrcAddr == server)
			{
				/* Drop packet */
				
				free(dPacket);
				dPacket = nullptr;
				break;
			}
		}

		return 0;
	}


	/* No IP header. Skip this packet */

	return 0;
}

