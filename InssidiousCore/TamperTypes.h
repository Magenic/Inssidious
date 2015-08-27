
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
	QString("Redirected to Poral"),
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

