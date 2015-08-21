
#include "C:\temp\clumsy-master\external\WinDivert-1.1.7-MSVC\include\windivert.h"
#pragma comment(lib, "C:\\temp\\clumsy-master\\external\\WinDivert-1.1.7-MSVC\\x86\\windivert.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")


class Packet
{
public:
	char *packet;
	UINT packetLen;
	WINDIVERT_ADDRESS addr;
	DWORD timestamp; // ! timestamp isn't filled when creating node since it's only needed for lag
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

class TamperModule
{
public:
	virtual short process(PacketList* packetList) = 0;
	virtual ~TamperModule() {}
	
	short resolutionSet = 0;

	short calcChance(short chance)
	{
		// notice that here we made a copy of chance, so even though it's volatile it is still ok
		return (chance == 10000) || ((rand() % 10000) < chance);
	}
};

class LagModule : public TamperModule
{

public:
	LagModule();
	~LagModule();
	short process(PacketList* packetList) override;

	volatile short lagTime;

private:
	Packet lagHeadNode = Packet{ 0 }, lagTailNode = Packet{ 0 };
	Packet *bufHead = &lagHeadNode, *bufTail = &lagTailNode;
	int bufSize = 0;

	short isBufEmpty();
	
};

class ThrottleModule : public TamperModule
{
public:
	ThrottleModule();
	~ThrottleModule();
	short process(PacketList* packetList) override;

private:
	volatile short chance = 1000; // [0-10000]

	// time frame in ms, when a throttle start the packets within the time 
	// will be queued and sent altogether when time is over
	volatile short throttleFrame;

	Packet throttleHeadNode = Packet{ 0 }, throttleTailNode = Packet{ 0 };
	Packet *bufHead = &throttleHeadNode, *bufTail = &throttleTailNode;
	int bufSize = 0;
	DWORD throttleStartTick = 0;

	short isBufEmpty();
	
};

class ResetModule : public TamperModule
{
public:
	~ResetModule();
	short process(PacketList* packetList) override;

private:
	volatile short chance = 0; // [0-10000]
	volatile short setNextCount = 0;

	const unsigned int TCP_MIN_SIZE = sizeof(WINDIVERT_IPHDR) + sizeof(WINDIVERT_TCPHDR);
};

class JitterModule : public TamperModule
{
public:
	JitterModule();
	~JitterModule();
	short process(PacketList* packetList) override;

	volatile short jitterVarianceInMs;
private:
	Packet jitterHeadNode = Packet{ 0 }, jitterTailNode = Packet{ 0 };
	Packet *bufHead = &jitterHeadNode, *bufTail = &jitterTailNode;
	int bufSize = 0;

	short isBufEmpty();
};

class DropPacketsModule : public TamperModule
{
public:
	~DropPacketsModule();
	short process(PacketList* packetList) override;

private:
	volatile short chance = 1000; // [0-10000]

};

class CorruptPacketsModule : public TamperModule
{
public:
	CorruptPacketsModule();
	~CorruptPacketsModule();
	short process(PacketList* packetList) override;

private:
	volatile short chance = 1000; // [0 - 10000]
	volatile short doChecksum = 1; // recompute checksum after after tampering

	// patterns covers every bit
	char patterns[8];
	int patIx = 0; // put this here to give a more random results

	inline void tamper_buf(char* buf, UINT len);
};

class NoPacketsModule : public TamperModule
{
public:
	~NoPacketsModule();
	short process(PacketList* packetList) override;
};

class NoDNSModule : public TamperModule
{
public:
	~NoDNSModule();
	short process(PacketList* packetList) override;
};

class NoServerModule : public TamperModule
{
public:
	~NoServerModule();
	short process(PacketList* packetList) override;
};

class NoSSLModule : public TamperModule
{
public:
	~NoSSLModule();
	short process(PacketList* packetList) override;
};

class RedirToPortalModule : public TamperModule
{
public:
	~RedirToPortalModule();
	short process(PacketList* packetList) override;
};

class HTTPHTTPSOnlyModule : public TamperModule
{
public:
	~HTTPHTTPSOnlyModule();
	short process(PacketList* packetList) override;

private:
	volatile short chance = 1000; // [0 - 10000]
};

class SiteBlockedModule : public TamperModule
{
public:
	~SiteBlockedModule();
	short process(PacketList* packetList) override;
};
