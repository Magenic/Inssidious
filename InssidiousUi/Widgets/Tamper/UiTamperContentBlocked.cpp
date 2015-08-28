#include "UiTamperContentBlocked.h"

UiTamperContentBlocked::UiTamperContentBlocked(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	contentBlockedButton = new QPushButton();
	contentBlockedButton->setCheckable(true);

	domainLabel = new QLabel("Blocked Domains:");
	domainComboBox = new QComboBox();
	domainComboBox->setEditable(true);
	domainComboBox->lineEdit()->setReadOnly(true);
	domainEditButton = new QPushButton("Edit");

	contentBlockedLayout = new QGridLayout();
	contentBlockedLayout->addWidget(contentBlockedButton, 0, 0, 1, 3);

	contentBlockedLayout->addWidget(domainLabel, 1, 0);
	contentBlockedLayout->addWidget(domainComboBox, 1, 1);
	contentBlockedLayout->addWidget(domainEditButton, 1, 2);

	moduleLayout->addLayout(contentBlockedLayout);
}

UiTamperContentBlocked::~UiTamperContentBlocked()
{

}
