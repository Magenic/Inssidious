#ifndef UITAMPERHTTPCORRUPTEDRESPONSE_H
#define UITAMPERHTTPCORRUPTEDRESPONSE_H

#include "UiTamperModule.h"

class UiTamperHTTPCorruptedResponse : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperHTTPCorruptedResponse(QWidget *parent, TamperType tamperType);
	~UiTamperHTTPCorruptedResponse();

private:
	QLayout* httpCorruptedLayout;
};

#endif // UITAMPERHTTPCORRUPTEDRESPONSE_H
