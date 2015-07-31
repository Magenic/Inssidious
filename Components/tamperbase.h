#ifndef TAMPERBASE_H
#define TAMPERBASE_H

#include <QObject>

class TamperBase : public QObject
{
	Q_OBJECT

public:
	TamperBase(QObject *parent);
	~TamperBase();

private:
	
};

#endif // TAMPERBASE_H
