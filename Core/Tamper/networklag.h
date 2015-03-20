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
	bool open(QString, QSettings);

	bool tamper();
	bool stop();

signals:
	void activity();
	void testTamperActivity();

public slots: 
	void onTestTamperActivity();
};

#endif // NETWORKLAG_H