#ifndef UITAMPERHTTPUNEXPECTEDRESPONSE_H
#define UITAMPERHTTPUNEXPECTEDRESPONSE_H

#include "UiTamperModule.h"

class UiTamperHTTPUnexpectedResponse : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperHTTPUnexpectedResponse(QWidget *parent, TamperType tamperType);
	~UiTamperHTTPUnexpectedResponse();

private:
	QLayout* httpUnexpectedLayout;
};

#endif // UITAMPERHTTPUNEXPECTEDRESPONSE_H
