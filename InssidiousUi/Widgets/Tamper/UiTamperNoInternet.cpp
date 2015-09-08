#include "UiTamperNoInternet.h"

UiTamperNoInternet::UiTamperNoInternet(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	
	pTamperConfig = (void*)new TamperNoInternetConfig{ false, false };

	noInternetDescriptionLabel = new QLabel();
	noInternetDescriptionLabel->setText(noInternetText);
	noInternetDescriptionLabel->setContentsMargins(0, 6, 0, 20);
	noInternetDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noInternetDescriptionLabel->setFont(moduleTextFont);
	noInternetDescriptionLabel->setPalette(moduleTextPalette);

	noTrafficDescriptionLabel = new QLabel();
	noTrafficDescriptionLabel->setText(noTrafficDescriptionText);
	noTrafficDescriptionLabel->setFixedHeight(20);
	noTrafficDescriptionLabel->setAlignment(Qt::AlignCenter);
	noTrafficDescriptionLabel->setFont(moduleTextFont);
	noTrafficDescriptionLabel->setPalette(moduleTextPalette);


	noTrafficButton = new QPushButton();
	noTrafficButton->setCheckable(true);
	noTrafficButton->setStyleSheet(buttonStyleSheet);
	noTrafficButton->setFixedSize(156, 30);
	noTrafficButton->setText("Block Internet Access");
	noTrafficButton->setAttribute(Qt::WA_TransparentForMouseEvents);

	redirDescriptionLabel = new QLabel();
	redirDescriptionLabel->setText(redirDescriptionText);
	redirDescriptionLabel->setFixedHeight(20);
	redirDescriptionLabel->setAlignment(Qt::AlignCenter);
	redirDescriptionLabel->setFont(moduleTextFont);
	redirDescriptionLabel->setPalette(moduleTextPalette);


	redirButton = new QPushButton();
	redirButton->setCheckable(true);
	redirButton->setStyleSheet(buttonStyleSheet);
	redirButton->setFixedSize(130, 30);
	redirButton->setText("Redirect to Portal");


	noInternetLayout = new QGridLayout();
	noInternetLayout->setHorizontalSpacing(30);
	noInternetLayout->setAlignment(Qt::AlignHCenter);
	noInternetLayout->setContentsMargins(10, 0, 10, 0);
	noInternetLayout->addWidget(noInternetDescriptionLabel, 1, 0/*, 1, 2*/);
	noInternetLayout->addWidget(noTrafficButton, 2, 0, Qt::AlignHCenter);
	//noInternetLayout->addWidget(redirButton, 2, 1, Qt::AlignHCenter);


	connect(noTrafficButton, &QPushButton::clicked, this, &UiTamperNoInternet::onNoTrafficButtonClicked);

	moduleLayout->addLayout(noInternetLayout);
}

UiTamperNoInternet::~UiTamperNoInternet()
{

}
void UiTamperNoInternet::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		noTrafficButton->setEnabled(true);
		noTrafficButton->setChecked(true);
		redirButton->setEnabled(true);

		noTrafficButton->setText("Blocking Internet Access");


		/* Set the config value to true */

		((TamperNoInternetConfig*)pTamperConfig)->localNetwork = true;


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);


		/* Uncheck and disable all buttons */

		noTrafficButton->setChecked(false);
		noTrafficButton->setText("Block Internet Access");
		noTrafficButton->setDisabled(true); 
		redirButton->setDisabled(true);


		/* Set the config value to false */

		((TamperNoInternetConfig*)pTamperConfig)->localNetwork = false;


		/* Notify Core */

		emit tamperStop(this);
	}
}

void UiTamperNoInternet::onNoTrafficButtonClicked()
{
	if (noTrafficButton->isChecked())
	{
		this->setActive(true);
	}
	else
	{
		this->setActive(false);
	}
}