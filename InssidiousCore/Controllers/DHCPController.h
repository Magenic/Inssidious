#ifndef DHCPCONTROLLER_H
#define DHCPCONTROLLER_H

#include <QThread>
#include <Windows.h>

class DHCPController : public QThread
{
	Q_OBJECT

public:
	DHCPController(QObject *parent);
	~DHCPController();

signals: 
	void ipAddressAssigned(QString MACAddress, QString ipAddress);


private:

	void run() override;


	HANDLE divertDHCPHandle;

	const QString divertDHCPFilterString = QString("ip.SrcAddr == 192.168.25.1 and udp.SrcPort == 67");
	const INT16 divertDHCPPriority = -100; /* higher priority than the default 0 */


	const int DHCPOptionsOffset = 240;
	const int DHCPMessageTypeOption = 53;
	const int DHCPACK = 5;
	const QString dhcpMagicCookie = "63825363";
};

#endif // DHCPCONTROLLER_H
