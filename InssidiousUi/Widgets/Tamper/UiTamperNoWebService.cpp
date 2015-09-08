#include "UiTamperNoWebService.h"

UiTamperNoWebService::UiTamperNoWebService(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperNoWebServiceConfig{ false };

	noWebServiceDescriptionLabel = new QLabel();
	noWebServiceDescriptionLabel->setText(noWebServiceDescriptionText);
	noWebServiceDescriptionLabel->setContentsMargins(0, 6, 0, 20);
	noWebServiceDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noWebServiceDescriptionLabel->setFont(moduleDescriptionFont);
	noWebServiceDescriptionLabel->setPalette(moduleTextPaletteInactive);

	blockWebServicesButton = new QPushButton();
	blockWebServicesButton->setCheckable(true);
	blockWebServicesButton->setStyleSheet(buttonStyleSheet);
	blockWebServicesButton->setFixedSize(130, 30);
	blockWebServicesButton->setText(blockedServiceTextFront + QString::number(blockedServicesCount) + blockedServiceTextBack);
		

	configWebServicesButton = new QPushButton();
	configWebServicesButton->setStyleSheet(buttonStyleSheet);
	configWebServicesButton->setFixedSize(130, 30);
	configWebServicesButton->setText("Configure Block List");
	

	noWebServiceLayout = new QGridLayout();
	noWebServiceLayout->setHorizontalSpacing(20);
	noWebServiceLayout->setAlignment(Qt::AlignHCenter);
	noWebServiceLayout->addWidget(noWebServiceDescriptionLabel, 1, 0, 1, 2);
	noWebServiceLayout->addWidget(blockWebServicesButton, 2, 0, Qt::AlignHCenter);
	noWebServiceLayout->addWidget(configWebServicesButton, 2, 1, Qt::AlignHCenter);



	moduleLayout->addLayout(noWebServiceLayout);
}

UiTamperNoWebService::~UiTamperNoWebService()
{

}
void UiTamperNoWebService::toggleState(bool active)
{
	if (active)
	{
		noWebServiceDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		blockWebServicesButton->setEnabled(true);
		configWebServicesButton->setEnabled(true);
	}
	else
	{
		noWebServiceDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		blockWebServicesButton->setDisabled(true);
		configWebServicesButton->setDisabled(true);
	}
}
