/*
*  File:		devices.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#ifndef DEVICES_H
#define DEVICES_H

#include <QtWidgets\QWidget>

class Devices : public QWidget
{
	Q_OBJECT

public:
	Devices(QWidget *parent);
	~Devices();

	void addTab(/* identifier */);
	void removeTab(/* identifier */);
	
	
private:
	
};

#endif // DEVICES_H
