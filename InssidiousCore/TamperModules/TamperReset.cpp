#include <InssidiousCore/TamperModules/TamperBase.h>

#define NAME "reset"

short ResetModule::process(PacketList* packetList)
{
	short reset = FALSE;
	Packet *pac = packetList->head->next;
	while (pac != packetList->tail) {
		if (/*checkDirection(pac->addr.Direction, resetInbound, resetOutbound)*/
			/*&&*/ pac->packetLen > TCP_MIN_SIZE
			&& (setNextCount || calcChance(chance)))
		{
			PWINDIVERT_TCPHDR pTcpHdr;
			WinDivertHelperParsePacket(
				pac->packet,
				pac->packetLen,
				NULL,
				NULL,
				NULL,
				NULL,
				&pTcpHdr,
				NULL,
				NULL,
				NULL);

			if (pTcpHdr != NULL) {
				//LOG("injecting reset w/ chance %.1f%%", chance / 100.0);
				pTcpHdr->Rst = 1;
				WinDivertHelperCalcChecksums(pac->packet, pac->packetLen, 0);

				reset = TRUE;
				if (setNextCount > 0) {
					InterlockedDecrement16(&setNextCount);
				}
			}
		}

		pac = pac->next;
	}

	return reset;

}

ResetModule::~ResetModule()
{
	
}
