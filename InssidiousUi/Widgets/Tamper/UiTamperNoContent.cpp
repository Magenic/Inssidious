#include "UiTamperNoContent.h"

UiTamperNoContent::UiTamperNoContent(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{

	pTamperConfig = (void*)new TamperNoContentConfig{ false };

	noContentButton = new QPushButton();
	noContentButton->setCheckable(true);
	noContentButton->setStyleSheet(buttonStyleSheet);
	noContentButton->setFixedSize(160, 30);
	noContentButton->setText("???");


	noContentLayout = new QGridLayout();
	noContentLayout->setSpacing(0);
	noContentLayout->setAlignment(Qt::AlignHCenter);
	//noContentLayout->addWidget(noContentButton, 0, 0, Qt::AlignHCenter);


	connect(noContentButton, &QPushButton::clicked, this, &UiTamperNoContent::onNoTrafficButtonClicked);

	moduleLayout->addLayout(noContentLayout);
}

UiTamperNoContent::~UiTamperNoContent()
{

}
void UiTamperNoContent::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		noContentButton->setEnabled(true);
		noContentButton->setChecked(true);


		/* Set the config value to true */

		((TamperNoContentConfig*)pTamperConfig)->something = true;


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);


		/* Uncheck and disable all buttons */

		noContentButton->setChecked(false);
		noContentButton->setDisabled(true);


		/* Set the config value to false */

		((TamperNoContentConfig*)pTamperConfig)->something = false;


		/* Notify Core */

		emit tamperStop(this);
	}
}

void UiTamperNoContent::onNoTrafficButtonClicked()
{
	if (noContentButton->isChecked())
	{
		this->setActive(true);
	}
	else
	{
		this->setActive(false);
	}
}