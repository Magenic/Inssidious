#include "UiTamperNoInternet.h"

UiTamperNoInternet::UiTamperNoInternet(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	
	pTamperConfig = (void*)new TamperNoInternetConfig{ false, false };

	noInternetDescriptionLabel = new QLabel();
	noInternetDescriptionLabel->setText(noInternetText);
	noInternetDescriptionLabel->setFixedHeight(12);
	noInternetDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noInternetDescriptionLabel->setFont(moduleDescriptionFont);
	noInternetDescriptionLabel->setPalette(moduleTextPaletteInactive);

	noTrafficDescriptionLabel = new QLabel();
	noTrafficDescriptionLabel->setText(noTrafficDescriptionText);
	noTrafficDescriptionLabel->setFixedHeight(30);
	noTrafficDescriptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	noTrafficDescriptionLabel->setFont(moduleDescriptionFont);
	noTrafficDescriptionLabel->setPalette(moduleTextPaletteInactive);


	noTrafficButton = new QPushButton();
	noTrafficButton->setCheckable(true);
	noTrafficButton->setStyleSheet(buttonStyleSheet);
	noTrafficButton->setFixedSize(120, 24);
	noTrafficButton->setText("No Internet Access");
	noTrafficButton->setDisabled(true);

	redirDescriptionLabel = new QLabel();
	redirDescriptionLabel->setText(redirDescriptionText);
	redirDescriptionLabel->setFixedHeight(30);
	redirDescriptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	redirDescriptionLabel->setFont(moduleDescriptionFont);
	redirDescriptionLabel->setPalette(moduleTextPaletteInactive);


	redirButton = new QPushButton();
	redirButton->setCheckable(true);
	redirButton->setStyleSheet(buttonStyleSheet);
	redirButton->setFixedSize(120, 24);
	redirButton->setText("Redirect to Portal");
	redirButton->setDisabled(true);


	noInternetLayout = new QGridLayout();
	noInternetLayout->setAlignment(Qt::AlignHCenter);
	noInternetLayout->setContentsMargins(10, 0, 10, 0);
	noInternetLayout->addItem(new QSpacerItem(0, 6), 0, 0);
	noInternetLayout->addWidget(noInternetDescriptionLabel, 1, 0, 1, 2);
	noInternetLayout->addItem(new QSpacerItem(0, 12), 2, 0);
	noInternetLayout->addWidget(noTrafficDescriptionLabel, 3, 0);
	noInternetLayout->addWidget(noTrafficButton, 3, 1);
	noInternetLayout->addItem(new QSpacerItem(0, 2), 4, 0);
	noInternetLayout->addWidget(redirDescriptionLabel, 5, 0);
	noInternetLayout->addWidget(redirButton, 5, 1);


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
		redirButton->setEnabled(true);
	}
	else
	{
		noInternetDescriptionLabel->setPalette(moduleTextPaletteInactive);
		noTrafficDescriptionLabel->setPalette(moduleTextPaletteInactive);
		redirDescriptionLabel->setPalette(moduleTextPaletteInactive);

		if (noTrafficButton->isChecked())
		{
			noTrafficButton->setChecked(false);
			noTrafficButton->clicked();
		}

		noTrafficButton->setDisabled(true);
		redirButton->setDisabled(true);
	}
}

void UiTamperNoInternet::onNoTrafficButtonClicked()
{
	if (noTrafficButton->isChecked())
	{
		((TamperNoInternetConfig*)pTamperConfig)->localNetwork = true;
	}
	else
	{
		((TamperNoInternetConfig*)pTamperConfig)->localNetwork = false;
	}
}