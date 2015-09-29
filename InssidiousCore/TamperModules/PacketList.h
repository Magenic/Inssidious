#ifndef DIVERTPACKET_H
#define DIVERTPACKET_H



#include <WinDivert/include/windivert.h>


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")


class DivertPacket
{
public:
	char packet[0xFFFF];
	UINT packetLength;
	WINDIVERT_ADDRESS addr;
};

typedef struct _PacketListEntry
{
	SLIST_ENTRY ItemEntry;
	char packet[0xFFFF];
	UINT packetLength;
	WINDIVERT_ADDRESS addr;
	DWORD releaseTimestamp = 0;
	HANDLE divertHandle = 0;
} PacketListEntry;


//class PacketList
//{
//
//public:
//	PacketList();
//
//	Packet headNode = Packet{ 0 }, tailNode = Packet{ 0 };
//	Packet * const head = &headNode, *const tail = &tailNode;
//
//	short isListEmpty();
//
//	void freeNode(Packet *node);
//	Packet* createNode(char* buf, UINT len, WINDIVERT_ADDRESS *addr);
//	Packet* popNode(Packet *node);
//	Packet* insertBefore(Packet *node, Packet *target);
//	Packet* insertAfter(Packet *node, Packet *target);
//	Packet* appendNode(Packet *node);
//
//};


#endif //DIVERTPACKET_H