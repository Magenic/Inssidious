#ifndef DHCPCONTROLLER_H
#define DHCPCONTROLLER_H

#include <QThread>
#include <Windows.h>

class DHCPController : public QThread
{
	Q_OBJECT

public:
	DHCPController(QObject* parent);


signals: 
	void ipAddressAssigned(QString MACAddress, QString ipAddress);


private:

	void run() override;


	HANDLE divertDHCPHandle;

	char* divertDHCPFilterString;
	const INT16 divertDHCPPriority = -100; /* higher priority than the default 0 */


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
