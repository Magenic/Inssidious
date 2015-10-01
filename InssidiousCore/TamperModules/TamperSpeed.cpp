#include "TamperSpeed.h"
#include <timeapi.h>


TamperSpeed::TamperSpeed(void** ppTamperConfig, PSLIST_HEADER packetSList)
{

	this->ppTamperSpeedConfig = reinterpret_cast<TamperSpeedConfig**>(ppTamperConfig);
	this->packetSList = packetSList;


}


short TamperSpeed::process(DivertPacket *& dPacket)
{

	if ((*ppTamperSpeedConfig)->speedType == SPEED_MAX)
	{
		/* Don't process these packets */

		return 0;
	}


	/* Get the current time to log with the packet */
	
	DWORD releaseTime;
	DWORD currentTime = timeGetTime();

	if (lastReleaseTime > currentTime)
	{
		releaseTime = lastReleaseTime;
	}
	else
	{
		releaseTime = currentTime;
	}


	/* Allocate memory for the packet list entry */

	PacketListEntry* pPacketListEntry = static_cast<PacketListEntry*>(_aligned_malloc(sizeof(PacketListEntry), MEMORY_ALLOCATION_ALIGNMENT));
	if (!pPacketListEntry)
	{
		__debugbreak();
	}

	/* Copy the dPacket values and set the packet release time */

	memcpy(pPacketListEntry->packet, dPacket->packet, dPacket->packetLength);
	pPacketListEntry->packetLength = dPacket->packetLength;
	memcpy(&(pPacketListEntry->addr), &dPacket->addr, sizeof(WINDIVERT_ADDRESS));
	pPacketListEntry->releaseTimestamp = releaseTime;


	/* Add the entry to the list */

	InterlockedPushEntrySList(packetSList, &(pPacketListEntry->ItemEntry));


	/* Increment the next packet's release time */

	releaseTime += TamperSpeedPacketDelay[(*ppTamperSpeedConfig)->speedType] / 2; /* enum defining millisecond values for different speed */
	lastReleaseTime = releaseTime;


	/* Drop the dPacket */

	free(dPacket);
	dPacket = nullptr;



	return 0;
	
};