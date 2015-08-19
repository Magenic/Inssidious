#ifndef PACKETBASE_H
#define PACKETBASE_H

#include "C:\temp\clumsy-master\external\WinDivert-1.1.7-MSVC\include\windivert.h"
#pragma comment(lib, "C:\\temp\\clumsy-master\\external\\WinDivert-1.1.7-MSVC\\x86\\windivert.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")


class PacketList
{

public:

	//Packet Linked List
	typedef struct _NODE {
		char *packet;
		UINT packetLen;
		WINDIVERT_ADDRESS addr;
		DWORD timestamp; // ! timestamp isn't filled when creating node since it's only needed for lag
		struct _NODE *prev, *next;
	} PacketNode;

	PacketNode headNode = _NODE{ 0 }, tailNode = _NODE{ 0 };
	PacketNode * const head = &headNode, *const tail = &tailNode;

	void initPacketNodeList();
	
	PacketNode* createNode(char* buf, UINT len, WINDIVERT_ADDRESS *addr);
	void freeNode(PacketNode *node);
	PacketNode* popNode(PacketNode *node);
	PacketNode* insertBefore(PacketNode *node, PacketNode *target);
	PacketNode* insertAfter(PacketNode *node, PacketNode *target);
	PacketNode* appendNode(PacketNode *node);
	
	
	short isListEmpty();
};


#endif //PACKETBASE_H