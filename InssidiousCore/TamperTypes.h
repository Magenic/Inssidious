
#include <QString>


enum TamperClass
{
	CONDITIONS,
	RESTRICTIONS,
	NETWORK_FAILURES,
	WEB_SERVICE_FAILURES,
	NUM_TAMPER_CLASSES
};

static QString TamperClassName[]
{
	QString("Network Conditions"),
	QString("Network Restrictions"),
	QString("Network Failures"),
	QString("Web Service Failures")
};


enum TamperType
{
	/* network condition */
	SPEED,
	DELAY,
	QUALITY,

	/* network restrictions */
	REDIR_TO_PORAL,
	CONTENT_BLOCKED,
	HTTP_HTTPS_ONLY,

	/* network failures */
	NO_INTERNET,
	NO_DNS,
	NO_SERVER,

	/* web service failures */
	HTTP_TIME_OUT,
	HTTP_UNEXPECTED_RESPONSE,
	HTTP_CORRUPTED_RESPONSE,

	/* total*/
	NUM_TAMPER_TYPES
};

static QString TamperTypeName[NUM_TAMPER_TYPES]
{
	QString("Speed"),
	QString("Delay"),
	QString("Quality"),
	QString("Redirected to Portal"),
	QString("Content Blocked by Filter"),
	QString("HTTP(S) Traffic Only"),
	QString("Internet is Unreachable"),
	QString("DNS Server is Unreachable"),
	QString("Your Server is Unreachable"),
	QString("HTTP Time Out"),
	QString("Unexpected HTTP Response"),
	QString("Corrupted HTTP Response")
};

static QString TamperTypeDescription[NUM_TAMPER_TYPES]
{
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text"),
	QString("Description Text")
};

static QString TamperTypeActiveIcon[NUM_TAMPER_TYPES]
{
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png")
};

static QString TamperTypeInactiveIcon[NUM_TAMPER_TYPES]
{
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png")
};

enum TamperSpeedTypes
{
	SPEED_EDGE,
	SPEED_3G,
	SPEED_4G,
	SPEED_LTE,
	SPEED_MAX
};

static const short TamperSpeedTimes[5]
{
	/* Average speeds pulled from http://opensignal.com/reports/2015/02/state-of-lte-q1-2015/ */
	/* Speed in Bytes Per Second divided by a Maximum Transmission Unit of 1500 Bytes == Rough Packet Per Second */

	40,	 /* TIME_EDGE	2G/Edge		0.3Mbps				25pps		40ppms */
	8,	 /* TIME_3G		3G			1.5Mbps				125pps		8ppms  */
	4,	 /* TIME_4G     4G/HSPA+	2.5Mbps				208pps		4ppms  */
	2,   /* TIME_LTE    LTE			7.0Mbps (in US)		583pps		2ppms  */
	0    /* TIME_MAX													   */
};