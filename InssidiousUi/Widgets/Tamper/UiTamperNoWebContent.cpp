#include "UiTamperNoWebContent.h"

UiTamperNoWebContent::UiTamperNoWebContent(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{

	pTamperConfig = static_cast<void*>(new TamperNoWebContentConfig{ false });

	noWebContentButton = new QPushButton();
	noWebContentButton->setCheckable(true);
	noWebContentButton->setStyleSheet(buttonStyleSheet);
	noWebContentButton->setFixedSize(160, 30);
	noWebContentButton->setText("???");
	
	
	noWebContentLayout = new QGridLayout();
	noWebContentLayout->setSpacing(0);
	noWebContentLayout->setAlignment(Qt::AlignHCenter);
	//noWebContentLayout->addWidget(noWebContentButton, 0, 0, Qt::AlignHCenter);



	buttonImagePaletteActive.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/TamperNoWebContentActive.png")));
	buttonImagePaletteInactive.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/TamperNoWebContentInactive.png")));

	buttonImage = new QLabel(this);
	buttonImage->setPalette(buttonImagePaletteInactive);
	buttonImage->setAutoFillBackground(true);
	buttonImage->setGeometry(0, 0, 380, 120);
	buttonImage->setAttribute(Qt::WA_TransparentForMouseEvents);
	buttonImage->show();


	connect(noWebContentButton, &QPushButton::clicked, this, &UiTamperNoWebContent::onNoTrafficButtonClicked);

	moduleLayout->addLayout(noWebContentLayout);
}


void UiTamperNoWebContent::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);
		this->buttonImage->setPalette(buttonImagePaletteActive);


		/* Enable the buttons */

		noWebContentButton->setEnabled(true);
		noWebContentButton->setChecked(true);


		/* Set the config value to true */

		static_cast<TamperNoWebContentConfig*>(pTamperConfig)->something = true;


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);
		this->buttonImage->setPalette(buttonImagePaletteInactive);
		

		/* Uncheck and disable all buttons */

		noWebContentButton->setChecked(false);
		noWebContentButton->setDisabled(true);


		/* Set the config value to false */

		static_cast<TamperNoWebContentConfig*>(pTamperConfig)->something = false;


		/* Notify Core */

		emit tamperStop(this);
	}
}

void UiTamperNoWebContent::onNoTrafficButtonClicked()
{
	if (noWebContentButton->isChecked())
	{
		this->setActive(true);
	}
	else
	{
		this->setActive(false);
	}
}