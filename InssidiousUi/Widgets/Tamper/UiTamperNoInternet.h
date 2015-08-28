#ifndef UITAMPERNOINTERNET_H
#define UITAMPERNOINTERNET_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>

class UiTamperNoInternet : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoInternet(QWidget *parent, TamperType tamperType);
	~UiTamperNoInternet();

private:
	QGridLayout* noInternetLayout;
	QPushButton* noInternetButton;

};

#endif // UITAMPERNOINTERNET_H
