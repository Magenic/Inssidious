#include "UiTamperHTTPUnexpectedResponse.h"

UiTamperHTTPUnexpectedResponse::UiTamperHTTPUnexpectedResponse(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	//qButtonGroup = new QButtonGroup(this);
	//qButtonGroup->setExclusive(true);

	//bHTTP200Empty = new QPushButton("200 Empty Response", this);
	//bHTTP300Redir = new QPushButton("300 Redirect to /", this);
	//bHTTP400Auth = new QPushButton("400 Unauthorized", this);
	//bHTTP500Error = new QPushButton("500 Server Error", this);

	//bHTTP200Empty->setCheckable(true);
	//bHTTP300Redir->setCheckable(true);
	//bHTTP400Auth->setCheckable(true);
	//bHTTP500Error->setCheckable(true);

	//qButtonGroup->addButton(bHTTP200Empty, 1);
	//qButtonGroup->addButton(bHTTP300Redir, 2);
	//qButtonGroup->addButton(bHTTP400Auth, 3);
	//qButtonGroup->addButton(bHTTP500Error, 4);


	//domainLabel = new QLabel("Web Services:");
	//domainLabel->setPalette(this->moduleTextPaletteInactive);
	//domainComboBox = new QComboBox();
	//domainComboBox->setEditable(true);
	//domainComboBox->lineEdit()->setReadOnly(true);
	//domainComboBox->setDisabled(true);
	//domainEditButton = new QPushButton("Edit");

	//httpUnexpectedLayout = new QGridLayout();
	//httpUnexpectedLayout->addWidget(bHTTP200Empty, 0, 0);
	//httpUnexpectedLayout->addWidget(bHTTP300Redir, 0, 1);
	//httpUnexpectedLayout->addWidget(bHTTP400Auth, 1, 0);
	//httpUnexpectedLayout->addWidget(bHTTP500Error, 1, 1);
	//httpUnexpectedLayout->addWidget(domainLabel, 2, 0);
	//httpUnexpectedLayout->addWidget(domainComboBox, 2, 1);
	//httpUnexpectedLayout->addWidget(domainEditButton, 2, 2);


	//moduleLayout->addLayout(httpUnexpectedLayout);
}

UiTamperHTTPUnexpectedResponse::~UiTamperHTTPUnexpectedResponse()
{

}
void UiTamperHTTPUnexpectedResponse::toggleState(bool active)
{
	//if (active)
	//{
	//	domainLabel->setPalette(this->moduleTextPaletteActive);
	//	domainComboBox->setEnabled(true);
	//}
	//else
	//{
	//	domainLabel->setPalette(this->moduleTextPaletteInactive);
	//	domainComboBox->setDisabled(true);
	//}
}
