#ifndef UITAMPERHTTPTIMEOUT_H
#define UITAMPERHTTPTIMEOUT_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

class UiTamperHTTPTimeOut : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperHTTPTimeOut(QWidget *parent, TamperType tamperType);
	~UiTamperHTTPTimeOut();

private:
	QGridLayout* httpTimeOutLayout;
	QPushButton* httpTimeOutButton;

	QLabel* domainLabel;
	QComboBox* domainComboBox;
	QPushButton* domainEditButton;
};

#endif // UITAMPERHTTPTIMEOUT_H
