#ifndef DHCPCONTROLLER_H
#define DHCPCONTROLLER_H

#include <QThread>

class DHCPController : public QThread
{
	Q_OBJECT

public:
	DHCPController(QObject *parent);
	~DHCPController();

private:
	
};

#endif // DHCPCONTROLLER_H
