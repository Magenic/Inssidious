#ifndef DHCPCONTROLLER_H
#define DHCPCONTROLLER_H

#include <QThread>
#include <Windows.h>

class DHCPController : public QThread
{
	Q_OBJECT

public:
	DHCPController();


signals: 
	void ipAddressAssigned(QString MACAddress, QString ipAddress);


private:

	void run() override;


	QString divertDHCPFilterString;
	QString ipFirstOctect;
	unsigned int uintDHCPServerIP = 0;


	HANDLE divertDHCPRecvHandle;
	HANDLE divertDHCPSendHandle;

	const INT16 DIVERT_HIGHEST_PRIORITY = -1000; /* higher priority than the default 0 */
	const INT16 DIVERT_LOWEST_PRIORITY = 1000; /* higher priority than the default 0 */

	const short DIVERT_QUEUE_LEN_MAX = 8192;
	const short DIVERT_QUEUE_TIME_MAX = 2048;

	
	const unsigned short dhcpUDPSrcPort = 17152; //htons(67);
	const int DHCPOptionsOffset = 240;
	const int DHCPMessageTypeOption = 53;
	const int DHCPACK = 5;
	const QString dhcpMagicCookie = "63825363";


	unsigned char packet[0xFFFF];
	UINT packet_len = 0;
	unsigned char* data =  nullptr;
	UINT data_len = 0;
};

#endif // DHCPCONTROLLER_H
