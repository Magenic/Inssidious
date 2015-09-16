#include "UiTamperNoInternet.h"

UiTamperNoInternet::UiTamperNoInternet(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	
	pTamperConfig = (void*)new TamperNoInternetConfig{ false, false };


	noInternetLayout = new QGridLayout();
	noInternetLayout->setSpacing(0);
	noInternetLayout->setAlignment(Qt::AlignHCenter);


	buttonImagePaletteActive.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/TamperNoInternetActive.png")));
	buttonImagePaletteInactive.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/TamperNoInternetInactive.png")));

	buttonImage = new QLabel(this);
	buttonImage->setPalette(buttonImagePaletteInactive);
	buttonImage->setAutoFillBackground(true);
	buttonImage->setGeometry(0, 0, 380, 120);
	buttonImage->setAttribute(Qt::WA_TransparentForMouseEvents);
	buttonImage->show();



	moduleLayout->addLayout(noInternetLayout);
}


void UiTamperNoInternet::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);
		this->buttonImage->setPalette(buttonImagePaletteActive);


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


		/* Set the config value to false */

		((TamperNoInternetConfig*)pTamperConfig)->localNetwork = false;


		/* Notify Core */

		emit tamperStop(this);
	}
}