#include "PacketList.h"

#define assert(x) do {if (!(x)) {DebugBreak();} } while(0)

void PacketList::initPacketNodeList() {
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

// TODO  using malloc in the loop is not good for performance
//       just not sure I can write a better memory allocator
PacketList::PacketNode* PacketList::createNode(char* buf, UINT len, WINDIVERT_ADDRESS *addr) {
	PacketNode *newNode = (PacketNode*)malloc(sizeof(PacketNode));
	newNode->packet = (char*)malloc(len);
	memcpy(newNode->packet, buf, len);
	newNode->packetLen = len;
	memcpy(&(newNode->addr), addr, sizeof(WINDIVERT_ADDRESS));
	newNode->next = newNode->prev = NULL;
	return newNode;
}

void PacketList::freeNode(PacketNode *node) {
	assert((node != head) && (node != tail));
	free(node->packet);
	free(node);
}

PacketList::PacketNode* PacketList::popNode(PacketNode *node) {
	assert((node != head) && (node != tail));
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return node;
}

PacketList::PacketNode* PacketList::insertAfter(PacketNode *node, PacketNode *target) {
	assert(node && node != head && node != tail && target != tail);
	node->prev = target;
	node->next = target->next;
	target->next->prev = node;
	target->next = node;
	return node;
}

PacketList::PacketNode* PacketList::insertBefore(PacketNode *node, PacketNode *target) {
	assert(node && node != head && node != tail && target != head);
	node->next = target;
	node->prev = target->prev;
	target->prev->next = node;
	target->prev = node;
	return node;
}

PacketList::PacketNode* PacketList::appendNode(PacketNode *node) {
	return insertBefore(node, tail);
}

short PacketList::isListEmpty() {
	return head->next == tail;

}