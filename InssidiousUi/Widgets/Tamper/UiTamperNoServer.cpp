#include "UiTamperNoServer.h"

UiTamperNoServer::UiTamperNoServer(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	noServerButton = new QPushButton();
	noServerButton->setCheckable(true);

	domainLabel = new QLabel("Domain Names:");
	domainComboBox = new QComboBox();
	domainComboBox->setEditable(true);
	domainComboBox->lineEdit()->setReadOnly(true);
	domainEditButton = new QPushButton("Edit");


	noServerLayout = new QGridLayout();
	noServerLayout->addWidget(noServerButton, 0, 0, 1, 3);
	noServerLayout->addWidget(domainLabel, 1, 0);
	noServerLayout->addWidget(domainComboBox, 1, 1);
	noServerLayout->addWidget(domainEditButton, 1, 2);


	moduleLayout->addLayout(noServerLayout);
}

UiTamperNoServer::~UiTamperNoServer()
{

}
