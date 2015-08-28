#include "UiTamperHTTPTimeOut.h"

UiTamperHTTPTimeOut::UiTamperHTTPTimeOut(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	httpTimeOutButton = new QPushButton();
	httpTimeOutButton->setCheckable(true);

	domainLabel = new QLabel("Web Services:");
	domainComboBox = new QComboBox();
	domainComboBox->setEditable(true);
	domainComboBox->lineEdit()->setReadOnly(true);
	domainEditButton = new QPushButton("Edit");

	httpTimeOutLayout = new QGridLayout();
	httpTimeOutLayout->addWidget(httpTimeOutButton, 0, 0, 1, 3);
	httpTimeOutLayout->addWidget(domainLabel, 1, 0);
	httpTimeOutLayout->addWidget(domainComboBox, 1, 1);
	httpTimeOutLayout->addWidget(domainEditButton, 1, 2);

	moduleLayout->addLayout(httpTimeOutLayout);
}

UiTamperHTTPTimeOut::~UiTamperHTTPTimeOut()
{

}
