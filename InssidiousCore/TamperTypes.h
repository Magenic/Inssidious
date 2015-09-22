#ifndef TAMPERTYPES_H
#define TAMPERTYPES_H

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include <list>

extern "C"
PSLIST_ENTRY __fastcall InterlockedPushListSList(
	IN PSLIST_HEADER ListHead,
	IN PSLIST_ENTRY List,
	IN PSLIST_ENTRY ListEnd,
	IN ULONG Count
	);


enum TamperType
{
	/* scenarios */
	SPEED,
	CONDITIONS,
	FIREWALL,
	DAMAGE,

	/* failures */
	NO_INTERNET,
	NO_SERVER,
	NO_WEB_CONTENT,
	WEBSERVICE_FAILURES,

	/* total*/
	NUM_TAMPER_TYPES
};


enum TamperSpeedType
{
	SPEED_EDGE,
	SPEED_3G,
	SPEED_4G,
	SPEED_LTE,
	SPEED_MAX
};

struct TamperSpeedConfig
{
	volatile TamperSpeedType speedType;
};



static const short TamperSpeedPacketDelay[5]
{
	/* Average speeds pulled from http://opensignal.com/reports/2015/02/state-of-lte-q1-2015/ */
	/* Bytes Per Second -> Packets Per Second by dividing by an average Maximum Transmission Unit of 1500 bytes */
	/* Packets Per Second -> Milliseconds Per Packet to get the amount of time to lag each packet */

	40,	 /* SPEED_EDGE		2G/Edge		0.3Mbps				25pps		40mspp  */
	8,	 /* SPEED_3G		3G			1.5Mbps				125pps		8pmspp  */
	4,	 /* SPEED_4G	    4G/HSPA+	2.5Mbps				208pps		4pmspp  */
	2,   /* SPEED_LTE		LTE			7.0Mbps (in US)		583pps		2mspp   */
	0    /* SPEED_MAX														    */
};



struct TamperConditionsConfig
{
	volatile short chanceLoss;
	volatile short chanceDelay;
	volatile short chanceCorrupt;
	volatile short chanceReset;
};

enum TamperFirewallType
{
	FIREWALL_EMAIL,
	FIREWALL_UDP,
	FIREWALL_VPN,
	FIREWALL_CUSTOM,
	FIREWALL_OFF
};

struct TamperFirewallConfig
{
	volatile TamperFirewallType firewallType;
	PSLIST_HEADER customPortList;
};

typedef struct _TamperFirewallEntry 
{
	SLIST_ENTRY ItemEntry;
	unsigned short version;
	unsigned short portNumber;
} TamperFirewallEntry;

/* Firewall Port lists */
static std::list<unsigned short> emailPortList = { 25, 26, 110, 143, 465, 587, 993, 995, 2525, 2526 };
static std::list<unsigned short> httpPortList = { 80 };
static std::list<unsigned short> httpsPortList = { 443 };
static std::list<unsigned short> sshPortList = { 22 };
static std::list<unsigned short> vpnPortList = { 47, 50, 500, 1701, 1723, 4500, 10000 };



struct TamperDamageConfig
{
	volatile short chanceDamage;
	volatile short chanceClose;
};


struct TamperNoInternetConfig
{
	volatile bool noInternet;
};

enum TamperNoServersType
{
	NO_SERVERS_CUSTOM,
	NO_SERVERS_OFF
};

struct TamperNoServerConfig
{
	volatile TamperNoServersType noServersType;
	PSLIST_HEADER noServersList;
};

typedef struct _TamperNoServerEntry
{
	SLIST_ENTRY ItemEntry;
	UINT32 version;
	UINT32 server;
} TamperNoServerEntry;


struct TamperNoWebContentConfig
{
	volatile bool something;
};


struct TamperWebServiceFailuresConfig
{
	volatile bool blockWebService;
};


#endif