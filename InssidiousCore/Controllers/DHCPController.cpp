#include "DHCPController.h"


#include <comdef.h>

#include <WinDivert/include/windivert.h>


DHCPController::DHCPController()
	: divertDHCPFilterString("ip.SrcAddr == 192.168.137.1 or ip.DstAddr == 192.168.137.1\0")
{

	/* Open a WinDivert handle to capture all traffic to and from the DHCP server */

	divertDHCPRecvHandle = WinDivertOpen(divertDHCPFilterString, WINDIVERT_LAYER_NETWORK, DIVERT_HIGHEST_PRIORITY, WINDIVERT_FLAG_NO_CHECKSUM);
	if (divertDHCPRecvHandle == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();
		
		/* Something went wrong */

		MessageBox(nullptr, reinterpret_cast<const wchar_t*>(QString(
			           ("Unable to load WinDivert. Error: \n   ")
			           + QString::fromWCharArray(_com_error(result).ErrorMessage())
		           ).utf16()),
			L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);

		return;
	}

	/* Maximize the WinDivert Queue time and length for these packets */

	WinDivertSetParam(divertDHCPRecvHandle, WINDIVERT_PARAM_QUEUE_LEN, DIVERT_QUEUE_LEN_MAX);
	WinDivertSetParam(divertDHCPRecvHandle, WINDIVERT_PARAM_QUEUE_TIME, DIVERT_QUEUE_TIME_MAX);


	/* Open another WinDivert handle with the lowest possible priority to reinject captured packets with */

	divertDHCPSendHandle = WinDivertOpen(divertDHCPFilterString, WINDIVERT_LAYER_NETWORK, DIVERT_HIGHEST_PRIORITY, WINDIVERT_FLAG_NO_CHECKSUM);
	if (divertDHCPSendHandle == INVALID_HANDLE_VALUE)
	{
		HRESULT result = GetLastError();

		/* Something went wrong */

		MessageBox(nullptr, reinterpret_cast<const wchar_t*>(QString(
			("Unable to load WinDivert. Error: \n   ")
			+ QString::fromWCharArray(_com_error(result).ErrorMessage())
			).utf16()),
			L"Inssidious failed to start.", MB_OK);
		ExitProcess(1);

		return;
	}

	/* DHCP Send Handle should never see packets, and we do not have a WinDivertRecv waiting on it. */
	/* Lower the WinDivert Queue time and length to drop anything that does end up there. */

	WinDivertSetParam(divertDHCPSendHandle, WINDIVERT_PARAM_QUEUE_LEN, 1 /*minimum queue length*/);
	WinDivertSetParam(divertDHCPSendHandle, WINDIVERT_PARAM_QUEUE_TIME, 128 /*minimum queue time*/);
}


void DHCPController::run()
{
	WINDIVERT_ADDRESS addr;
	PWINDIVERT_IPHDR pIPHdr;
	PWINDIVERT_UDPHDR pUDPHdr;
	unsigned int dhcpServerIP = inet_addr("192.168.137.1");

	while (true)
	{

		/* Wait for a DHCP packet */

		if (!WinDivertRecv(divertDHCPRecvHandle, packet, sizeof(packet), &addr, &packet_len))
		{
			/* Something went wrong */

			//TODO: Handle this error
			HRESULT result = GetLastError();
			continue;
		}


		/* Grab the DHCP data from the packet */

		if(!WinDivertHelperParsePacket(packet, packet_len, &pIPHdr, 0, 0, 0, 0, &pUDPHdr, reinterpret_cast<void**>(&data), &data_len))
		{			
			/* Something went wrong; malformed packet maybe? 
			   We should be able to continue without concern */

			continue;
		}


		/* Send the packet on its way */

		WinDivertHelperCalcChecksums(packet, packet_len, WINDIVERT_HELPER_NO_REPLACE);
		WinDivertSendEx(divertDHCPSendHandle, packet, packet_len, 0 /* reserved */, &addr, nullptr, nullptr);


		/* Check if either pIPHdr or pUDPHdr are null */

		if (!pIPHdr || !pUDPHdr)
		{
			/* We don't want to parse this packet */

			continue;
		}


		/* Check if this is a UDP packet from the DHCP Server on the right port */

		if (pIPHdr->SrcAddr != dhcpServerIP || pUDPHdr->SrcPort != dhcpUDPSrcPort)
		{
			/* We don't want to parse this packet */

			continue;
		}


		/* Check if we have a DHCP packet */

		if (data_len < 240 || dhcpMagicCookie != QByteArray(reinterpret_cast<const char*>(&data[236]), 4).toHex())
		{
			/* Not sure what kind of packet this is but we don't want it */

			continue;
		}


		/* Find the DHCP Message Type option to test if this is a DHCP ACK message */

		int offset = DHCPOptionsOffset; 
		while (offset < data_len && offset != 255 /* DHCP Options End*/ )
		{

			if (data[offset] != DHCPMessageTypeOption)
			{
				/* Not the right option, check another */

				offset += 2 + data[offset + 1]  /* option size */;
				continue;
			}

			if (data[offset + 2] != DHCPACK)
			{
				/* Found a Message Type but it wasn't an DHCP ACK message. Leave the option-parsing loop */
				
				break;
			}


			/* This is a DHCP ACK message, grab the IP and MAC Addresses */

			QString yourIPAddress = QString::number(data[16]) + "." + QString::number(data[17]) + "." + QString::number(data[18]) + "." + QString::number(data[19]);
			QString clientHardwareAddress = QByteArray(reinterpret_cast<const char*>(&data[28]), 6).toHex();
			
			for (int i = 2; i < clientHardwareAddress.size(); i += 3)
			{
				/* Insert hyphens into the MAC address string */
				clientHardwareAddress.insert(i, "-");
			}


			/* If we read valid IP and MAC Addresses, notify Core */

			if (yourIPAddress.startsWith("192")	&& !clientHardwareAddress.contains("00:00:00:00:00:00"))
			{
				emit ipAddressAssigned(clientHardwareAddress.toUpper(), yourIPAddress);
			}


			/* Leave the option-parsing while loop */

			break;
		}

		/* Swing back to WinDivertRecv */
	}

	/* Never reached */
}