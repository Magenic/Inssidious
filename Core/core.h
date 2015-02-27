#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QString>

class Core : public QObject
{
	Q_OBJECT

public:
	Core();
	~Core();

public slots:
	void start();

signals:
	void coreStarted();
	void coreStartFailed(QString string);

private:

};

#endif // CORE_H
