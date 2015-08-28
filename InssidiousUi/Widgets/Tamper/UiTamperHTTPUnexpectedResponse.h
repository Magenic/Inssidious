#ifndef UITAMPERHTTPUNEXPECTEDRESPONSE_H
#define UITAMPERHTTPUNEXPECTEDRESPONSE_H

#include "UiTamperModule.h"
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

class UiTamperHTTPUnexpectedResponse : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperHTTPUnexpectedResponse(QWidget *parent, TamperType tamperType);
	~UiTamperHTTPUnexpectedResponse();

private:

	QGridLayout* httpUnexpectedLayout;
	QButtonGroup* qButtonGroup;
	QPushButton* bHTTP200Empty;
	QPushButton* bHTTP300Redir;
	QPushButton* bHTTP400Auth;
	QPushButton* bHTTP500Error;

	QLabel* domainLabel;
	QComboBox* domainComboBox;
	QPushButton* domainEditButton;
};

#endif // UITAMPERHTTPUNEXPECTEDRESPONSE_H
