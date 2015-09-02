#ifndef TAMPERTYPES_H
#define TAMPERTYPES_H


#include <QString>


enum TamperType
{
	/* network condition */
	SPEED,
	CONDITIONS,
	FIREWALL,

	/* network failures */
	NO_INTERNET,
	NO_SERVER,
	NO_WEBSERVICE,

	/* web service failures */
	//HTTP_TIME_OUT,
	//HTTP_UNEXPECTED_RESPONSE,
	//HTTP_CORRUPTED_RESPONSE,

	/* total*/
	NUM_TAMPER_TYPES
};


static QString TamperTypeName[NUM_TAMPER_TYPES]
{
	QString("Network Speed"),
		QString("Network Conditions"),
		QString("Network Firewall"),
		QString("Internet Access"),
		QString("Server Access"),
		QString("Web Service Access"),
		//QString(""),
		//QString(""),
		//QString("")
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


struct TamperFirewallConfig
{
	volatile bool allowHTTP;
	volatile bool allowHTTPS;
	volatile bool contentBlocked;
};


struct TamperNoInternetConfig
{
	volatile bool localNetwork;
	volatile bool redirToPortal;
};


struct TamperNoServerConfig
{
	volatile bool blockServers;
};


struct TamperNoWebServiceConfig
{
	volatile bool blockWebService;
};


#endif