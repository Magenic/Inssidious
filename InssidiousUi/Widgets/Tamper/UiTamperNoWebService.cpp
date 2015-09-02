#include "UiTamperNoWebService.h"

UiTamperNoWebService::UiTamperNoWebService(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperNoWebServiceConfig{ false };

	noWebServiceDescriptionLabel = new QLabel();
	noWebServiceDescriptionLabel->setText(noWebServiceDescriptionText);
	noWebServiceDescriptionLabel->setFixedHeight(12);
	noWebServiceDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noWebServiceDescriptionLabel->setFont(moduleDescriptionFont);
	noWebServiceDescriptionLabel->setPalette(moduleTextPaletteInactive);

	noWebServiceButton = new QPushButton();
	noWebServiceButton->setCheckable(true);
	noWebServiceButton->setStyleSheet(buttonDoubleWideStyleSheet);
	noWebServiceButton->setFixedSize(120, 24);
	noWebServiceButton->setText("Block Web Services");
	noWebServiceButton->setDisabled(true);

	configWebServicesDescriptionLabel = new QLabel();
	configWebServicesDescriptionLabel->setText(configWebServicesDescriptionText);
	configWebServicesDescriptionLabel->setFixedHeight(30);
	configWebServicesDescriptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	configWebServicesDescriptionLabel->setFont(moduleDescriptionFont);
	configWebServicesDescriptionLabel->setPalette(moduleTextPaletteInactive);

	configWebServicesButton = new QPushButton();
	configWebServicesButton->setCheckable(true);
	configWebServicesButton->setStyleSheet(buttonMiddleStyleSheet);
	configWebServicesButton->setFixedSize(16, 16);
	configWebServicesButton->setText("");
	configWebServicesButton->setDisabled(true);

	noWebServiceLayout = new QGridLayout();
	noWebServiceLayout->setAlignment(Qt::AlignHCenter);
	noWebServiceLayout->setContentsMargins(10, 0, 10, 0);
	noWebServiceLayout->addItem(new QSpacerItem(0, 6), 0, 0);
	noWebServiceLayout->addWidget(noWebServiceDescriptionLabel, 1, 0, 1, 3);
	noWebServiceLayout->addItem(new QSpacerItem(0, 12), 2, 0);
	noWebServiceLayout->addWidget(noWebServiceButton, 3, 0, 1, 3, Qt::AlignHCenter);
	noWebServiceLayout->addItem(new QSpacerItem(0, 10), 4, 0);
	noWebServiceLayout->addWidget(configWebServicesDescriptionLabel, 5, 0, 1, 2, Qt::AlignLeft);
	noWebServiceLayout->addWidget(configWebServicesButton, 5, 2, Qt::AlignLeft);

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
		configWebServicesDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		noWebServiceButton->setEnabled(true);
		configWebServicesButton->setEnabled(true);
	}
	else
	{
		noWebServiceDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		configWebServicesDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		noWebServiceButton->setDisabled(true);
		configWebServicesButton->setDisabled(true);
	}
}
