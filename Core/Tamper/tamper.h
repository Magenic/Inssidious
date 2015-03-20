#ifndef TAMPER_H
#define TAMPER_H

#include "WinDivert\windivert.h"			//WinDivert functions and types

#include <QString>
#include <QSettings>

#pragma comment(lib, "WinDivert.lib")		//Link against iphlpapi.lib for IP Helper APIs

class Tamper : public QObject
{
	Q_OBJECT

public:
	virtual bool open(QString) = 0;
	virtual bool open(QString, QSettings) = 0;

	virtual bool tamper() = 0;
	virtual bool stop() = 0;

signals:
	void activity();

private:
	
};

#endif // TAMPER_H
