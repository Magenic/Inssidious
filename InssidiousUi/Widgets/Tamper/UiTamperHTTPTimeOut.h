#ifndef UITAMPERHTTPTIMEOUT_H
#define UITAMPERHTTPTIMEOUT_H

#include "UiTamperModule.h"

class UiTamperHTTPTimeOut : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperHTTPTimeOut(QWidget *parent, TamperType tamperType);
	~UiTamperHTTPTimeOut();

private:
	QLayout* httpTimeOutLayout;
};

#endif // UITAMPERHTTPTIMEOUT_H
