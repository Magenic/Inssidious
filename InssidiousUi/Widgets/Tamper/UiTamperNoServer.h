#ifndef UITAMPERNOSERVER_H
#define UITAMPERNOSERVER_H

#include "UiTamperModule.h"

class UiTamperNoServer : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoServer(QWidget *parent, TamperType tamperType);
	~UiTamperNoServer();

private:
	QLayout* noServerLayout;
};

#endif // UITAMPERNOSERVER_H
