#include "UiTamperNoInternet.h"

UiTamperNoInternet::UiTamperNoInternet(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	
	pTamperConfig = (void*)new TamperNoInternetConfig{ false, false };

	noInternetDescriptionLabel = new QLabel();
	noInternetDescriptionLabel->setText(noInternetText);
	noInternetDescriptionLabel->setContentsMargins(0, 6, 0, 20);
	noInternetDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noInternetDescriptionLabel->setFont(moduleDescriptionFont);
	noInternetDescriptionLabel->setPalette(moduleTextPaletteInactive);

	noTrafficDescriptionLabel = new QLabel();
	noTrafficDescriptionLabel->setText(noTrafficDescriptionText);
	noTrafficDescriptionLabel->setFixedHeight(20);
	noTrafficDescriptionLabel->setAlignment(Qt::AlignCenter);
	noTrafficDescriptionLabel->setFont(moduleDescriptionFont);
	noTrafficDescriptionLabel->setPalette(moduleTextPaletteInactive);


	noTrafficButton = new QPushButton();
	noTrafficButton->setCheckable(true);
	noTrafficButton->setStyleSheet(buttonStyleSheet);
	noTrafficButton->setFixedSize(156, 30);
	noTrafficButton->setText("Block Internet Access");


	redirDescriptionLabel = new QLabel();
	redirDescriptionLabel->setText(redirDescriptionText);
	redirDescriptionLabel->setFixedHeight(20);
	redirDescriptionLabel->setAlignment(Qt::AlignCenter);
	redirDescriptionLabel->setFont(moduleDescriptionFont);
	redirDescriptionLabel->setPalette(moduleTextPaletteInactive);


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
void UiTamperNoInternet::toggleState(bool active)
{
	if (active)
	{
		noInternetDescriptionLabel->setPalette(moduleTextPaletteActive);
		noTrafficDescriptionLabel->setPalette(moduleTextPaletteActive);
		redirDescriptionLabel->setPalette(moduleTextPaletteActive);
		noTrafficButton->setEnabled(true);
		noTrafficButton->setChecked(true);
		redirButton->setEnabled(true);

		noTrafficButton->setText("Blocking Internet Access");
		((TamperNoInternetConfig*)pTamperConfig)->localNetwork = true;
	}
	else
	{
		noInternetDescriptionLabel->setPalette(moduleTextPaletteInactive);
		noTrafficDescriptionLabel->setPalette(moduleTextPaletteInactive);
		redirDescriptionLabel->setPalette(moduleTextPaletteInactive);


		noTrafficButton->setChecked(false);
		noTrafficButton->setText("Block Internet Access");
		((TamperNoInternetConfig*)pTamperConfig)->localNetwork = false;

	}
}

void UiTamperNoInternet::onNoTrafficButtonClicked()
{
	emit tamperButtonClicked(this, pTamperConfig);
}