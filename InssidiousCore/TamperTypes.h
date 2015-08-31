
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

	


enum TamperSpeedTypes
{
	SPEED_EDGE,
	SPEED_3G,
	SPEED_4G,
	SPEED_LTE
};

static const short TamperSpeedTimes[5]
{
	/* Average speeds pulled from http://opensignal.com/reports/2015/02/state-of-lte-q1-2015/ */
	/* Speed in Bytes Per Second divided by a Maximum Transmission Unit of 1500 Bytes == Rough Packet Per Second */

	40,	 /* TIME_EDGE	2G/Edge		0.3Mbps				25pps		40ppms */
	8,	 /* TIME_3G		3G			1.5Mbps				125pps		8ppms  */
	4,	 /* TIME_4G     4G/HSPA+	2.5Mbps				208pps		4ppms  */
	2    /* TIME_LTE    LTE			7.0Mbps (in US)		583pps		2ppms  */
};