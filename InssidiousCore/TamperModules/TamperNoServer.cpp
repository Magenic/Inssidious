
#include "TamperNoServer.h"

TamperNoServer::TamperNoServer(void** ppTamperConfig)
{
	this->ppNoServerConfig = reinterpret_cast<TamperNoServerConfig**>(ppTamperConfig);
	serverListVersion = 0;
	serverList.clear();
}

short TamperNoServer::process(PacketList* packetList)
{
	if (packetList->head->next == packetList->tail)
	{
		/* No packets */

		return 0;
	}


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


			/* Loop continues until we get a null pop entry */

		}

		break;
	}
	case NO_SERVERS_OFF:
	default:
		return 0;
	}



	/* Loop and drop any packets traveling over blocked ports */

	Packet *pDivertPacket = packetList->head->next;
	while (pDivertPacket != packetList->tail)
	{
		WINDIVERT_IPHDR *iphdr = nullptr;
		WINDIVERT_TCPHDR *tcphdr = nullptr;
		WINDIVERT_UDPHDR *udphdr = nullptr;
		WinDivertHelperParsePacket(pDivertPacket->packet, pDivertPacket->packetLen, &iphdr, 0, 0, 0, &tcphdr, &udphdr, 0, 0);

		/* Drop packets travelling to/from blocked servers */

		if (iphdr)
		{
			pDivertPacket = pDivertPacket->next;

			for (UINT32 server : serverList)
			{
				if (iphdr->DstAddr == server || iphdr->SrcAddr == server)
				{
					/* Drop packet */
					packetList->freeNode(packetList->popNode(pDivertPacket->prev));
					break;
				}
			}

			continue;
		}


		/* No IP header. Skip this packet */

		pDivertPacket = pDivertPacket->next;
	}



	return 0;
}

