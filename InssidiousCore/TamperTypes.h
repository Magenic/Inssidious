
#include <QString>

enum TamperType
{
	CORRUPT,
	DROP,
	LAG,
	RESET,
	THROTTLE,
	SYN,
	ACK,
	LOL
};

static QString TamperTypeNames[]
{
	QString("Corrupt Packets"),
		QString("Drop Packets"),
		QString("Lag Packets"),
		QString("Reset Connection"),
		QString("Throttle Packets"),
		QString("Unimplemented"),
		QString("Unimplemented"),
		QString("Unimplemented")
};

static QString TamperTypeDescriptions[]
{
	QString("Corrupt Packets"),
		QString("Drop Packets"),
		QString("Lag Packets"),
		QString("Reset Connection"),
		QString("Throttle Packets"),
		QString("Unimplemented"),
		QString("Unimplemented"),
		QString("Unimplemented")
};

static QString TamperTypeActiveIcon[]
{
	QString(":/Tamper/CorruptPacketsActive.png"),
		QString(":/Tamper/DropPacketsActive.png"),
		QString(":/Tamper/LagPacketsActive.png"),
		QString(":/Tamper/ResetTCPConnectionActive.png"),
		QString(":/Tamper/ThrottlePacketsActive.png"),
		QString(":/Tamper/UnimplementedActive.png"),
		QString(":/Tamper/UnimplementedActive.png"),
		QString(":/Tamper/UnimplementedActive.png")
};

static QString TamperTypeInactiveIcon[]
{
	QString(":/Tamper/CorruptPacketsInactive.png"),
		QString(":/Tamper/DropPacketsInactive.png"),
		QString(":/Tamper/LagPacketsInactive.png"),
		QString(":/Tamper/ResetTCPConnectionInactive.png"),
		QString(":/Tamper/ThrottlePacketsInactive.png"),
		QString(":/Tamper/UnimplementedInactive.png"),
		QString(":/Tamper/UnimplementedInactive.png"),
		QString(":/Tamper/UnimplementedInactive.png")
};