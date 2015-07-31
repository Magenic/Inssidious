#ifndef TAMPERCOMPONENT_H
#define TAMPERCOMPONENT_H

#include <QObject>

class TamperComponent : public QObject
{
	Q_OBJECT

public:
	TamperComponent(QObject *parent);
	~TamperComponent();

private:
	
};

#endif // TAMPERCOMPONENT_H
