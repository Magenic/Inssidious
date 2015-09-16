#include "UiTamperFirewall.h"


UiTamperFirewall::UiTamperFirewall(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = static_cast<void*>(new TamperFirewallConfig{ true, true, false });

	buttonGroup = new QButtonGroup();
	buttonLeft = new QPushButton();
	buttonRight = new QPushButton();

	buttonLeft->setStyleSheet(buttonLeftStyleSheet90);
	buttonRight->setStyleSheet(buttonRightStyleSheet90);

	buttonLeft->setText("HTTP(S) Only");
	buttonRight->setText("Custom Rules");

	buttonLeft->setFixedSize(90, 30);
	buttonRight->setFixedSize(90, 30);

	buttonLeft->setFont(moduleTextFont);
	buttonRight->setFont(moduleTextFont);

	buttonLeft->setCheckable(true);
	buttonRight->setCheckable(true);

	firewallLayout = new QGridLayout();
	firewallLayout->setSpacing(0);
	firewallLayout->setMargin(0);
	firewallLayout->addWidget(buttonLeft, 0, 0, Qt::AlignRight);
	firewallLayout->addWidget(buttonRight, 0, 1, Qt::AlignLeft);

	buttonGroup->setExclusive(true);
	buttonGroup->addButton(buttonLeft, 0);
	buttonGroup->addButton(buttonRight, 1);

	buttonLeft->setDisabled(true);
	buttonRight->setDisabled(true);

	connect(buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &UiTamperFirewall::onButtonClicked);


	moduleLayout->addLayout(firewallLayout);
}


void UiTamperFirewall::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		buttonLeft->setEnabled(true);
		buttonRight->setEnabled(true);


		/* Set the speed to SPEED_LTE & check the button */

		//if (buttonGroup->checkedId() == -1)
		//{
		//	buttonRight->setChecked(true);
		//	onButtonClicked(SPEED_LTE);
		//}


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);


		/* Uncheck and disable all buttons */

		buttonGroup->setExclusive(false);

		buttonLeft->setChecked(false);
		buttonRight->setChecked(false);

		buttonLeft->setDisabled(true);
		buttonRight->setDisabled(true);

		buttonGroup->setExclusive(true);


		/* Set the speed back to MAX */

		//((TamperFirewallConfig*)pTamperConfig)->speedType = SPEED_MAX;


		/* Notify core to stop */

		emit tamperStop(this);
	}
}


void UiTamperFirewall::onButtonClicked(int index)
{
	//if (filterButton->isChecked())
	//{
	//	((TamperFirewallConfig*)pTamperConfig)->contentBlocked = true;
	//}
	//else
	//{
	//	((TamperFirewallConfig*)pTamperConfig)->contentBlocked = false;
	//}
}

