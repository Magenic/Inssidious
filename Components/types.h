/*
*  File:		types.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/

#ifndef TYPES_H
#define TYPES_H

typedef enum HostedNetworkReason
{
	HOSTED_NETWORK_STARTING,
	HOSTED_NETWORK_STARTING_FAILED,
	HOSTED_NETWORK_STARTED,
	HOSTED_NETWORK_STOPPED,
	DEVICE_CONNECTED,
	DEVICE_DISCONNECTED
};

#endif