#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

class Device : public QObject
{
	Q_OBJECT

public:
	Device(QObject *parent);
	~Device();

private:
	
};

#endif // DEVICE_H
