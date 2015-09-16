#include "DHCPController.h"

#include <WinDivert/include/windivert.h>
#include <comdef.h>

#pragma comment(lib, "..\\WinDivert\\x86\\WinDivert.lib")

DHCPController::DHCPController(QObject *parent)
	: QThread(parent)
{

	divertDHCPHandle = WinDivertOpen(divertDHCPFilterString.toLocal8Bit(), WINDIVERT_LAYER_NETWORK, divertDHCPPriority, WINDIVERT_FLAG_SNIFF);
	if (divertDHCPHandle == INVALID_HANDLE_VALUE)
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

}


void DHCPController::run()
{
	WINDIVERT_ADDRESS addr;

	while (true)
	{

		/* Wait for a DHCP packet */

		if (!WinDivertRecv(divertDHCPHandle, packet, sizeof(packet), &addr, &packet_len))
		{
			/* Something went wrong */

			//TODO: Handle this error
			HRESULT result = GetLastError();
			continue;
		}


		/* Grab the DHCP data from the packet */

		if(!WinDivertHelperParsePacket(packet, packet_len, 0, 0, 0, 0, 0, 0, reinterpret_cast<void**>(&data), &data_len))
		{			
			/* Something went wrong; malformed packet maybe? 
			   We should be able to continue without concern */

			continue;
		}


		/* Confirm we have a DHCP packet */

		if (dhcpMagicCookie != QByteArray(reinterpret_cast<const char*>(&data[236]), 4).toHex())
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