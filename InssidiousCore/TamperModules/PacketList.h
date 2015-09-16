#ifndef PACKETLIST_H
#define PACKETLIST_H



#include <WinDivert/include/windivert.h>


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")


class Packet
{
public:
	char *packet;
	UINT packetLen;
	WINDIVERT_ADDRESS addr;
	DWORD timestamp; 
	Packet *prev, *next;
};


class PacketList
{

public:
	PacketList();

	Packet headNode = Packet{ 0 }, tailNode = Packet{ 0 };
	Packet * const head = &headNode, *const tail = &tailNode;

	short isListEmpty();

	void freeNode(Packet *node);
	Packet* createNode(char* buf, UINT len, WINDIVERT_ADDRESS *addr);
	Packet* popNode(Packet *node);
	Packet* insertBefore(Packet *node, Packet *target);
	Packet* insertAfter(Packet *node, Packet *target);
	Packet* appendNode(Packet *node);

};


#endif //PACKETLIST_H