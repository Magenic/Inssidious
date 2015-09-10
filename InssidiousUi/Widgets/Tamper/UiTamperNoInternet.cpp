#include "UiTamperNoInternet.h"

UiTamperNoInternet::UiTamperNoInternet(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	
	pTamperConfig = (void*)new TamperNoInternetConfig{ false, false };

	noTrafficButton = new QPushButton();
	noTrafficButton->setCheckable(true);
	noTrafficButton->setStyleSheet(buttonLeftStyleSheet90);
	noTrafficButton->setFixedSize(90, 30);
	noTrafficButton->setText("Local Network Only");

	redirButton = new QPushButton();
	redirButton->setCheckable(true);
	redirButton->setStyleSheet(buttonRightStyleSheet90);
	redirButton->setFixedSize(90, 30);
	redirButton->setText("Captive Portal");


	noInternetLayout = new QGridLayout();
	noInternetLayout->setSpacing(0);
	noInternetLayout->setAlignment(Qt::AlignHCenter);
	//noInternetLayout->addWidget(noTrafficButton, 0, 0, Qt::AlignHCenter);
	//noInternetLayout->addWidget(redirButton, 0, 1, Qt::AlignHCenter);


	buttonImagePaletteActive.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/TamperNoInternetActive.png")));
	buttonImagePaletteInactive.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/TamperNoInternetInactive.png")));

	buttonImage = new QLabel(this);
	buttonImage->setPalette(buttonImagePaletteInactive);
	buttonImage->setAutoFillBackground(true);
	buttonImage->setGeometry(0, 0, 380, 120);
	buttonImage->setAttribute(Qt::WA_TransparentForMouseEvents);
	buttonImage->show();



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
		this->buttonImage->setPalette(buttonImagePaletteActive);


		/* Enable the buttons */

		noTrafficButton->setEnabled(true);
		noTrafficButton->setChecked(true);
		redirButton->setEnabled(true);

		//noTrafficButton->setText("Blocking Internet Access");


		/* Set the config value to true */

		((TamperNoInternetConfig*)pTamperConfig)->localNetwork = true;


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);
		this->buttonImage->setPalette(buttonImagePaletteInactive);


		/* Uncheck and disable all buttons */

		noTrafficButton->setChecked(false);
		//noTrafficButton->setText("Block Internet Access");
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