#include "UiTamperWebServiceFailures.h"

UiTamperWebServiceFailures::UiTamperWebServiceFailures(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperWebServiceFailuresConfig{ false };

	configWebServicesButton = new QPushButton();
	configWebServicesButton->setStyleSheet(buttonStyleSheet);
	configWebServicesButton->setFixedSize(130, 30);
	configWebServicesButton->setText("Configure Block List");

	buttonGroup = new QButtonGroup();
	buttonLeft = new QPushButton();
	buttonMiddle1 = new QPushButton();
	buttonMiddle2 = new QPushButton();
	buttonRight = new QPushButton();

	buttonLeft->setStyleSheet(buttonLeftStyleSheet90);
	buttonMiddle1->setStyleSheet(buttonMiddleStyleSheet90);
	buttonMiddle2->setStyleSheet(buttonMiddleStyleSheet90);
	buttonRight->setStyleSheet(buttonRightStyleSheet90);

	buttonLeft->setText("HTTP 200");
	buttonMiddle1->setText("HTTP 300");
	buttonMiddle2->setText("HTTP 400");
	buttonRight->setText("HTTP 500");

	buttonLeft->setFixedSize(90, 30);
	buttonMiddle1->setFixedSize(90, 30);
	buttonMiddle2->setFixedSize(90, 30);
	buttonRight->setFixedSize(90, 30);

	buttonLeft->setFont(moduleTextFont);
	buttonMiddle1->setFont(moduleTextFont);
	buttonMiddle2->setFont(moduleTextFont);
	buttonRight->setFont(moduleTextFont);

	buttonLeft->setCheckable(true);
	buttonMiddle1->setCheckable(true);
	buttonMiddle2->setCheckable(true);
	buttonRight->setCheckable(true);

	buttonGroup->setExclusive(true);
	buttonGroup->addButton(buttonLeft, 0);
	buttonGroup->addButton(buttonMiddle1, 1);
	buttonGroup->addButton(buttonMiddle2, 2);
	buttonGroup->addButton(buttonRight, 3);


	buttonLeft->setDisabled(true);
	buttonMiddle1->setDisabled(true);
	buttonMiddle2->setDisabled(true);
	buttonRight->setDisabled(true);


	connect(buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &UiTamperWebServiceFailures::onButtonClicked);



	webServiceFailuresLayout = new QGridLayout();
	webServiceFailuresLayout->setSpacing(0);
	webServiceFailuresLayout->setAlignment(Qt::AlignHCenter);
	webServiceFailuresLayout->addWidget(buttonLeft, 0, 0);
	webServiceFailuresLayout->addWidget(buttonMiddle1, 0, 1);
	webServiceFailuresLayout->addWidget(buttonMiddle2, 0, 2);
	webServiceFailuresLayout->addWidget(buttonRight, 0, 3);



	moduleLayout->addLayout(webServiceFailuresLayout);
}

UiTamperWebServiceFailures::~UiTamperWebServiceFailures()
{

}
void UiTamperWebServiceFailures::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		configWebServicesButton->setEnabled(true);

		buttonLeft->setEnabled(true);
		buttonMiddle1->setEnabled(true);
		buttonMiddle2->setEnabled(true);
		buttonRight->setEnabled(true);



		/* Set the config value to true and the block button to checked */

		((TamperWebServiceFailuresConfig*)pTamperConfig)->blockWebService = true;
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

		configWebServicesButton->setDisabled(true);

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

		
		
		/* Set the config value to false */

		((TamperWebServiceFailuresConfig*)pTamperConfig)->blockWebService = false;
		//((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_MAX;


		/* Notify Core */

		emit tamperStop(this);
	}
}


void UiTamperWebServiceFailures::onButtonClicked(int button)
{
	//switch (buttonGroup->checkedId())
	//{
	//case -1:
	//	/* No Button Checked */
	//	((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_MAX;
	//	break;
	//case SPEED_EDGE:
	//	((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_EDGE;
	//	break;
	//case SPEED_3G:
	//	((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_3G;
	//	break;
	//case SPEED_4G:
	//	((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_4G;
	//	break;
	//case SPEED_LTE:
	//	((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_LTE;
	//	break;
	//case SPEED_MAX:
	//default:
	//	((TamperWebServiceFailuresConfig*)pTamperConfig)->speedType = SPEED_MAX;
	//	break;
	//}
}
