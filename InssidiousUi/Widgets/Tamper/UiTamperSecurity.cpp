#include "UiTamperSecurity.h"

UiTamperSecurity::UiTamperSecurity(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{

	pTamperConfig = (void*)new TamperSecurityConfig{ false };


	noTrafficButton = new QPushButton();
	noTrafficButton->setCheckable(true);
	noTrafficButton->setStyleSheet(buttonLeftStyleSheet90);
	noTrafficButton->setFixedSize(90, 30);
	noTrafficButton->setText("???");

	redirButton = new QPushButton();
	redirButton->setCheckable(true);
	redirButton->setStyleSheet(buttonRightStyleSheet90);
	redirButton->setFixedSize(90, 30);
	redirButton->setText("???");


	securityLayout = new QGridLayout();
	securityLayout->setSpacing(0);
	securityLayout->setAlignment(Qt::AlignHCenter);
	securityLayout->addWidget(noTrafficButton, 0, 0, Qt::AlignHCenter);
	securityLayout->addWidget(redirButton, 0, 1, Qt::AlignHCenter);


	noTrafficButton->setDisabled(true);
	redirButton->setDisabled(true);

	connect(noTrafficButton, &QPushButton::clicked, this, &UiTamperSecurity::onNoTrafficButtonClicked);

	moduleLayout->addLayout(securityLayout);
}

UiTamperSecurity::~UiTamperSecurity()
{

}
void UiTamperSecurity::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		noTrafficButton->setEnabled(true);
		noTrafficButton->setChecked(true);
		redirButton->setEnabled(true);


		/* Set the config value to true */

		((TamperSecurityConfig*)pTamperConfig)->something = true;


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);


		/* Uncheck and disable all buttons */

		noTrafficButton->setChecked(false);
		noTrafficButton->setDisabled(true);
		redirButton->setDisabled(true);


		/* Set the config value to false */

		((TamperSecurityConfig*)pTamperConfig)->something = false;


		/* Notify Core */

		emit tamperStop(this);
	}
}

void UiTamperSecurity::onNoTrafficButtonClicked()
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