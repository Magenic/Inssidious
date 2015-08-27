#ifndef UITAMPERHTTPHTTPSONLY_H
#define UITAMPERHTTPHTTPSONLY_H

#include "UiTamperModule.h"

class UiTamperHTTPHTTPSOnly : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperHTTPHTTPSOnly(QWidget *parent, TamperType tamperType);
	~UiTamperHTTPHTTPSOnly();

private:
	QLayout* httpHTTPSOnlyLayout;
};

#endif // UITAMPERHTTPHTTPSONLY_H
