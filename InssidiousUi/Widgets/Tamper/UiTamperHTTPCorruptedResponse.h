#ifndef UITAMPERHTTPCORRUPTEDRESPONSE_H
#define UITAMPERHTTPCORRUPTEDRESPONSE_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

class UiTamperHTTPCorruptedResponse : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperHTTPCorruptedResponse(QWidget *parent, TamperType tamperType);
	~UiTamperHTTPCorruptedResponse();

private:
	QGridLayout* httpCorruptedLayout;
	QPushButton* httpCorruptedButton;

	QLabel* domainLabel;
	QComboBox* domainComboBox;
	QPushButton* domainEditButton;
};

#endif // UITAMPERHTTPCORRUPTEDRESPONSE_H
