#ifndef UITAMPERNOINTERNET_H
#define UITAMPERNOINTERNET_H

#include "UiTamperModule.h"

class UiTamperNoInternet : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoInternet(QWidget *parent, TamperType tamperType);
	~UiTamperNoInternet();

private:
	QLayout* noInternetLayout;
};

#endif // UITAMPERNOINTERNET_H
