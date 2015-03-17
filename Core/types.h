#ifndef TYPES_H
#define TYPES_H


static enum DeviceType					//Device Types
{
	IPHONE,
	IPAD,
	ANDROIDPHONE,
	ANDROIDTABLET,
	MAC,
	WINDOWS,
	UNKNOWN
};

static enum TamperType					//Tamper Types
{
	NETWORK_LAG,
	DROP_ALL_TRAFFIC,
	DROP_NON_HTTP_TRAFFIC,
	REDIRECT_TO_PORTAL,
	WEB_SERVICE_ERROR,
	WEB_SERVICE_TIME_OUT,
	WEB_SERVICE_EMPTY_RESPONSES
};

static enum AdapterPhysType				//Adapter Types
{
	ETHERNET,
	WIRELESS,
	WIRELESS_HOSTED_NETWORK_CAPABLE
};

struct NetworkAdapter					//Network Adapter information
{
	QString AdapterName;
	QString AdapterDescription;
	AdapterPhysType AdapterType;
};



#endif // TYPES_H

