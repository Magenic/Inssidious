#include "networklag.h"


TamperNetworkLag::TamperNetworkLag()
{
	connect(this, &TamperNetworkLag::testTamperActivity, this, &TamperNetworkLag::onTestTamperActivity);
}


TamperNetworkLag::~TamperNetworkLag()
{
}

bool TamperNetworkLag::open(QString)
{
	return true;
}

bool TamperNetworkLag::open(QString, QSettings)
{
	return true;
}

bool TamperNetworkLag::tamper()
{
	
	emit testTamperActivity();
	return true;
}

bool TamperNetworkLag::stop()
{
	return true;
}

void TamperNetworkLag::onTestTamperActivity()
{
		_sleep(3000);
		emit activity();
		_sleep(10000);
		emit activity();
}