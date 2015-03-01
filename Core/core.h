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
	void onThreadStart();
	void onInssidiousStart();

signals:
	void coreInitialized();
	void coreInitializeFailed(QString string);
	void coreStarted();
	void coreStartFailed(QString string);
	void inssidiousStarted();
	void inssidiousStartFailed(QString string);

private:

};

#endif // CORE_H
