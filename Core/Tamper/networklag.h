#ifndef NETWORKLAG_H
#define NETWORKLAG_H

#include "Core\Tamper\tamper.h"

class TamperNetworkLag : public Tamper
{
	Q_OBJECT

public:
	TamperNetworkLag();
	~TamperNetworkLag();

	bool open(QString);
	bool isActive = false;

signals:
	void activity();
	void failed();

public slots:
	void start();

private:
	QString* filter;
	HANDLE outboundTraffic;
	HANDLE inboundTraffic;

};

#endif // NETWORKLAG_H