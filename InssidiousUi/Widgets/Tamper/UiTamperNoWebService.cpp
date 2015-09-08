#include "UiTamperNoWebService.h"

UiTamperNoWebService::UiTamperNoWebService(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperNoWebServiceConfig{ false };

	noWebServiceDescriptionLabel = new QLabel();
	noWebServiceDescriptionLabel->setText(noWebServiceDescriptionText);
	noWebServiceDescriptionLabel->setContentsMargins(0, 6, 0, 20);
	noWebServiceDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noWebServiceDescriptionLabel->setFont(moduleTextFont);
	noWebServiceDescriptionLabel->setPalette(moduleTextPalette);


	blockWebServicesButton = new QPushButton();
	blockWebServicesButton->setCheckable(true);
	blockWebServicesButton->setStyleSheet(buttonStyleSheet);
	blockWebServicesButton->setFixedSize(130, 30);
	blockWebServicesButton->setText(blockedServiceTextFront + QString::number(blockedServicesCount) + blockedServiceTextBack);
	blockWebServicesButton->setAttribute(Qt::WA_TransparentForMouseEvents);


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
void UiTamperNoWebService::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		blockWebServicesButton->setEnabled(true);
		configWebServicesButton->setEnabled(true);


		/* Set the config value to true and the block button to checked */

		blockWebServicesButton->setChecked(true);
		((TamperNoWebServiceConfig*)pTamperConfig)->blockWebService = true;


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);

	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);


		/* Uncheck and disable all buttons */

		blockWebServicesButton->setChecked(false);

		blockWebServicesButton->setDisabled(true);
		configWebServicesButton->setDisabled(true);

		
		/* Set the config value to false */

		((TamperNoWebServiceConfig*)pTamperConfig)->blockWebService = false;


		/* Notify Core */

		emit tamperStop(this);
	}
}
