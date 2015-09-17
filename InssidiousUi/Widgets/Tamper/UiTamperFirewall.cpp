#include "UiTamperFirewall.h"
#include "Dialog/ConfigureFirewallDialog.h"


UiTamperFirewall::UiTamperFirewall(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = static_cast<void*>(new TamperFirewallConfig{ true, true, false });

	buttonGroup = new QButtonGroup();
	buttonLeft = new QPushButton();
	buttonMiddle1 = new QPushButton();
	buttonMiddle2 = new QPushButton();
	buttonRight = new QPushButton();

	buttonLeft->setStyleSheet(buttonLeftStyleSheet88);
	buttonMiddle1->setStyleSheet(buttonMiddleStyleSheet88);
	buttonMiddle2->setStyleSheet(buttonMiddleStyleSheet88);
	buttonRight->setStyleSheet(buttonRightStyleSheet88);

	buttonLeft->setText("Block Email");
	buttonMiddle1->setText("Block UDP");
	buttonMiddle2->setText("Block VPN");
	buttonRight->setText("Custom Rules");

	buttonLeft->setFixedSize(88, 30);
	buttonMiddle1->setFixedSize(88, 30);
	buttonMiddle2->setFixedSize(88, 30);
	buttonRight->setFixedSize(88, 30);

	buttonLeft->setCheckable(true);
	buttonMiddle1->setCheckable(true);
	buttonMiddle2->setCheckable(true);
	buttonRight->setCheckable(true);

	buttonLeft->setDisabled(true);
	buttonMiddle1->setDisabled(true);
	buttonMiddle2->setDisabled(true);
	buttonRight->setDisabled(true);

	buttonGroup->setExclusive(true);
	buttonGroup->addButton(buttonLeft, 0);
	buttonGroup->addButton(buttonMiddle1, 1);
	buttonGroup->addButton(buttonMiddle2, 2);
	buttonGroup->addButton(buttonRight, 3);



	firewallLayout = new QGridLayout();
	firewallLayout->setSpacing(0);
	firewallLayout->setMargin(0);
	firewallLayout->setAlignment(Qt::AlignHCenter);
	firewallLayout->addWidget(buttonLeft, 0, 0);
	firewallLayout->addWidget(buttonMiddle1, 0, 1);
	firewallLayout->addWidget(buttonMiddle2, 0, 2);
	firewallLayout->addWidget(buttonRight, 0, 3);

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
		buttonMiddle1->setEnabled(true);
		buttonMiddle2->setEnabled(true);
		buttonRight->setEnabled(true);


		/* Set Block Email to Checked */

		if (buttonGroup->checkedId() == -1)
		{
			buttonLeft->setChecked(true);
			onButtonClicked(0);
		}


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
		buttonMiddle1->setChecked(false);
		buttonMiddle2->setChecked(false);
		buttonRight->setChecked(false);

		buttonLeft->setDisabled(true);
		buttonMiddle1->setDisabled(true);
		buttonMiddle2->setDisabled(true);
		buttonRight->setDisabled(true);

		buttonGroup->setExclusive(true);


		/* Clear the button settings */

		onButtonClicked(-1);


		/* Notify core to stop */

		emit tamperStop(this);
	}
}


void UiTamperFirewall::onButtonClicked(int index)
{
	switch (buttonGroup->checkedId())
	{
	case -1:
		/* No Button Checked */
		//TODO
		//((TamperFirewallConfig*)pTamperConfig)-> = SPEED_MAX;
		break;
	case 0 /* Block Email */:
		//((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_EDGE;
		break;
	case 1 /* Block UDP */:
		//((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_3G;
		break;
	case 2 /* Block VPN */:
		//((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_4G;
		break;
	case 3 /* Custom Rules */:
	{
		QList<QString> stringList;
		ConfigureFirewallDialog* dialog = new ConfigureFirewallDialog(this->parentWidget(), &stringList);
		dialog->exec();
		delete dialog;
		//((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_LTE;
		break;
	}
	default:
		//	((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_MAX;
		break;
	}

}

