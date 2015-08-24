#include "TamperBase.h"

#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)

PacketList::PacketList() 
{
	if (head->next == NULL && tail->prev == NULL) {
		// first time initializing
		head->next = tail;
		tail->prev = head;
	}
	else {
		// have used before, then check node is empty
		assert(isListEmpty());
	}
}



Packet* PacketList::createNode(char* buf, UINT len, WINDIVERT_ADDRESS *addr) {
	Packet *newNode = (Packet*)malloc(sizeof(Packet));
	newNode->packet = (char*)malloc(len);
	memcpy(newNode->packet, buf, len);
	newNode->packetLen = len;
	memcpy(&(newNode->addr), addr, sizeof(WINDIVERT_ADDRESS));
	newNode->next = newNode->prev = NULL;
	return newNode;
}

void PacketList::freeNode(Packet *node) {
	assert((node != head) && (node != tail));
	free(node->packet);
	free(node);
}

Packet* PacketList::popNode(Packet *node) {
	assert((node != head) && (node != tail));
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return node;
}

Packet* PacketList::insertAfter(Packet *node, Packet *target) {
	assert(node && node != head && node != tail && target != tail);
	node->prev = target;
	node->next = target->next;
	target->next->prev = node;
	target->next = node;
	return node;
}

Packet* PacketList::insertBefore(Packet *node, Packet *target) {
	assert(node && node != head && node != tail && target != head);
	node->next = target;
	node->prev = target->prev;
	target->prev->next = node;
	target->prev = node;
	return node;
}

Packet* PacketList::appendNode(Packet *node) {
	return insertBefore(node, tail);
}

short PacketList::isListEmpty() {
	return head->next == tail;

}

