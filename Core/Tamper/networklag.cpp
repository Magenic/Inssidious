#include "networklag.h"


TamperNetworkLag::TamperNetworkLag()
{
	filter = new QString();
	isActive = false;

}


TamperNetworkLag::~TamperNetworkLag()
{
	if (outboundTraffic)
	{
		WinDivertClose(outboundTraffic);
		outboundTraffic = NULL;
	}
	
	if (inboundTraffic)
	{
		WinDivertClose(inboundTraffic);
		inboundTraffic = NULL;
	}
}

bool TamperNetworkLag::open(QString MACAddress)
{

	////Open a WinDivert handle for outbound traffic
	//outboundTraffic = WinDivertOpen(filter->toWCharArray,
	//	WINDIVERT_LAYER_NETWORK_FORWARD, /* outbound traffic is on the forward layer */
	//	NETWORK_LAG_PRIORITY,
	//	0 /* no flags */
	//	);

	////Open a WinDivert handle for inbound traffic
	//inboundTraffic = WinDivertOpen(filter->toWCharArray(),
	//	WINDIVERT_LAYER_NETWORK, /* inbound traffic is on the network layer */
	//	NETWORK_LAG_PRIORITY,
	//	0 /* no flags */
	//	);

	////Confirm both handles are valid
	//if (outboundTraffic == INVALID_HANDLE_VALUE || inboundTraffic == INVALID_HANDLE_VALUE)
	//{ /* one of the handles did not open successfully */
	//	emit failed();
	//	return false;
	//}

	return true;
}

void TamperNetworkLag::start()
{
	//isActive = true;
	//unsigned char packet[0xFFFF];
	//WINDIVERT_ADDRESS recv_addr;
	//UINT packet_len;

	//while (isActive)
	//{
	//	WinDivertRecv(inboundTraffic, packet, sizeof(packet), &recv_addr, &packet_len);

	//	WinDivertSend(inboundTraffic, packet, packet_len, &recv_addr, NULL);
	//}
}