#ifndef TAMPERCONTROLLER_H
#define TAMPERCONTROLLER_H

#include <QObject>

class TamperController : public QObject
{
	Q_OBJECT

public:
	TamperController(QObject *parent);
	~TamperController();

private:
	
};

#endif // TAMPERCONTROLLER_H
