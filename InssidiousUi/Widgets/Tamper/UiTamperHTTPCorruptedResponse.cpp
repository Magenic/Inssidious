#include "UiTamperHTTPCorruptedResponse.h"

UiTamperHTTPCorruptedResponse::UiTamperHTTPCorruptedResponse(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	//httpCorruptedButton = new QPushButton();
	//httpCorruptedButton->setCheckable(true);

	//domainLabel = new QLabel("Web Services:");
	//domainLabel->setPalette(this->moduleTextPaletteInactive);
	//domainComboBox = new QComboBox();
	//domainComboBox->setEditable(true);
	//domainComboBox->lineEdit()->setReadOnly(true);
	//domainComboBox->setDisabled(true);
	//domainEditButton = new QPushButton("Edit");

	//httpCorruptedLayout = new QGridLayout();
	//httpCorruptedLayout->addWidget(httpCorruptedButton, 0, 0, 1, 3);
	//httpCorruptedLayout->addWidget(domainLabel, 1, 0);
	//httpCorruptedLayout->addWidget(domainComboBox, 1, 1);
	//httpCorruptedLayout->addWidget(domainEditButton, 1, 2);

	//moduleLayout->addLayout(httpCorruptedLayout);
}

UiTamperHTTPCorruptedResponse::~UiTamperHTTPCorruptedResponse()
{

}
void UiTamperHTTPCorruptedResponse::toggleState(bool active)
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
