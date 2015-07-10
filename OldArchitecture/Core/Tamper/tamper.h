#ifndef TAMPER_H
#define TAMPER_H

#include "WinDivert\windivert.h"			//WinDivert functions and types
#include "Core\types.h"						//Tamper priorities

#include <QString>
#include <QSettings>

#pragma comment(lib, "WinDivert.lib")		//Link against iphlpapi.lib for IP Helper APIs

class Tamper : public QObject
{
	Q_OBJECT

public:
	virtual bool open(QString) = 0;
	bool isActive;

signals:
	void activity();
	void failed();

public slots:
	virtual void start() = 0;

};

#endif // TAMPER_H
