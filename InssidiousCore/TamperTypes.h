
#include <QString>


enum TamperClass
{
	SPEED,
	NOISE,
	FAILURE,
	RESTRICTION,
	NUM_TAMPER_CLASSES
};

static QString TamperClassName[]
{
	QString("Network Speed"),
	QString("Network Noise"),
	QString("Network Failures"),
	QString("Network Restrictions")
};


enum TamperType
{
	/* speed */
	LAG,
	THROTTLE,

	/* noise */
	RESET,
	JITTER,
	DROPPED_PACKETS,
	CORRUPT_PACKETS,

	/* failures */
	NO_PACKETS,
	NO_DNS,
	NO_SERVER,
	NO_SSL,

	/* restrictions */
	REDIR_TO_PORTAL,
	HTTP_HTTPS_ONLY,
	SITE_BLOCKED,

	/* total*/
	NUM_TAMPER_TYPES
};

static QString TamperTypeName[]
{
	QString("Lag"),
	QString("Throttle"),
	QString("TCP Resets"),
	QString("Packet Jitter"),
	QString("Dropped Packets"),
	QString("Corrupted Packets"),
	QString("No Packets"),
	QString("No DNS"),
	QString("No Server"),
	QString("No SSL"),
	QString("Redirected to Portal"),
	QString("HTTP and HTTPS Only"),
	QString("Site Blocked")
};

static QString TamperTypeDescription[]
{
	QString("Lag"),
	QString("Throttle"),
	QString("TCP Resets"),
	QString("Packet Jitter"),
	QString("Dropped Packets"),
	QString("Corrupted Packets"),
	QString("No Packets"),
	QString("No DNS"),
	QString("No Server"),
	QString("No SSL"),
	QString("Redirected to Portal"),
	QString("HTTP and HTTPS Only"),
	QString("Site Blocked")
};

static QString TamperTypeActiveIcon[]
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
	QString(":/Tamper/UnimplementedActive.png"),
	QString(":/Tamper/UnimplementedActive.png"),
};

static QString TamperTypeInactiveIcon[]
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
	QString(":/Tamper/UnimplementedInactive.png"),
	QString(":/Tamper/UnimplementedInactive.png"),
};