#include "UiTamperNoDNS.h"

UiTamperNoDNS::UiTamperNoDNS(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{

	noDNSButton = new QPushButton();
	noDNSButton->setCheckable(true);

	domainLabel = new QLabel("Additional DNS Servers:");
	domainComboBox = new QComboBox();
	domainComboBox->setEditable(true);
	domainComboBox->lineEdit()->setReadOnly(true);
	domainEditButton = new QPushButton("Edit");

	noDNSLayout = new QGridLayout();
	noDNSLayout->addWidget(noDNSButton, 0, 0, 1, 3);
	noDNSLayout->addWidget(domainLabel, 1, 0);
	noDNSLayout->addWidget(domainComboBox, 1, 1);
	noDNSLayout->addWidget(domainEditButton, 1, 2);

	moduleLayout->addLayout(noDNSLayout);
}

UiTamperNoDNS::~UiTamperNoDNS()
{

}
