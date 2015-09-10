#include "UiTamperNoWebService.h"

UiTamperNoWebService::UiTamperNoWebService(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperNoWebServiceConfig{ false };

	configWebServicesButton = new QPushButton();
	configWebServicesButton->setStyleSheet(buttonStyleSheet);
	configWebServicesButton->setFixedSize(130, 30);
	configWebServicesButton->setText("Configure Block List");

	buttonGroup = new QButtonGroup();
	buttonLeft = new QPushButton();
	buttonMiddle1 = new QPushButton();
	buttonMiddle2 = new QPushButton();
	buttonMiddle3 = new QPushButton();
	buttonRight = new QPushButton();

	buttonLeft->setStyleSheet(buttonLeftStyleSheet60);
	buttonMiddle1->setStyleSheet(buttonMiddleStyleSheet60);
	buttonMiddle2->setStyleSheet(buttonMiddleStyleSheet60);
	buttonMiddle3->setStyleSheet(buttonMiddleStyleSheet60);
	buttonRight->setStyleSheet(buttonRightStyleSheet60);

	buttonLeft->setText("Time Out");
	buttonMiddle1->setText("HTTP 200");
	buttonMiddle2->setText("HTTP 300");
	buttonMiddle3->setText("HTTP 400");
	buttonRight->setText("HTTP 500");

	buttonLeft->setFixedSize(60, 30);
	buttonMiddle1->setFixedSize(60, 30);
	buttonMiddle2->setFixedSize(60, 30);
	buttonMiddle3->setFixedSize(60, 30);
	buttonRight->setFixedSize(60, 30);

	buttonLeft->setFont(moduleTextFont);
	buttonMiddle1->setFont(moduleTextFont);
	buttonMiddle2->setFont(moduleTextFont);
	buttonMiddle3->setFont(moduleTextFont);
	buttonRight->setFont(moduleTextFont);

	buttonLeft->setCheckable(true);
	buttonMiddle1->setCheckable(true);
	buttonMiddle2->setCheckable(true);
	buttonMiddle3->setCheckable(true);
	buttonRight->setCheckable(true);

	buttonGroup->setExclusive(true);
	buttonGroup->addButton(buttonLeft, 0);
	buttonGroup->addButton(buttonMiddle1, 1);
	buttonGroup->addButton(buttonMiddle2, 2);
	buttonGroup->addButton(buttonMiddle3, 3);
	buttonGroup->addButton(buttonRight, 4);


	buttonLeft->setDisabled(true);
	buttonMiddle1->setDisabled(true);
	buttonMiddle2->setDisabled(true);
	buttonMiddle3->setDisabled(true);
	buttonRight->setDisabled(true);


	connect(buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &UiTamperNoWebService::onButtonClicked);



	noWebServiceLayout = new QGridLayout();
	noWebServiceLayout->setSpacing(0);
	noWebServiceLayout->setAlignment(Qt::AlignHCenter);
	noWebServiceLayout->addWidget(buttonLeft, 0, 0);
	noWebServiceLayout->addWidget(buttonMiddle1, 0, 1);
	noWebServiceLayout->addWidget(buttonMiddle2, 0, 2);
	noWebServiceLayout->addWidget(buttonMiddle3, 0, 3);
	noWebServiceLayout->addWidget(buttonRight, 0, 4);



	moduleLayout->addLayout(noWebServiceLayout);
}

UiTamperNoWebService::~UiTamperNoWebService()
{

}
void UiTamperNoWebService::setActive(bool active)
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
		buttonMiddle3->setEnabled(true);
		buttonRight->setEnabled(true);



		/* Set the config value to true and the block button to checked */

		((TamperNoWebServiceConfig*)pTamperConfig)->blockWebService = true;
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
		buttonMiddle3->setChecked(false);
		buttonRight->setChecked(false);

		buttonLeft->setDisabled(true);
		buttonMiddle1->setDisabled(true);
		buttonMiddle2->setDisabled(true);
		buttonMiddle3->setDisabled(true);
		buttonRight->setDisabled(true);

		buttonGroup->setExclusive(true);

		
		
		/* Set the config value to false */

		((TamperNoWebServiceConfig*)pTamperConfig)->blockWebService = false;
		//((TamperSpeedConfig*)pTamperConfig)->speedType = SPEED_MAX;


		/* Notify Core */

		emit tamperStop(this);
	}
}


void UiTamperNoWebService::onButtonClicked(int button)
{
	//switch (buttonGroup->checkedId())
	//{
	//case -1:
	//	/* No Button Checked */
	//	((TamperNoWebServiceConfig*)pTamperConfig)->speedType = SPEED_MAX;
	//	break;
	//case SPEED_EDGE:
	//	((TamperNoWebServiceConfig*)pTamperConfig)->speedType = SPEED_EDGE;
	//	break;
	//case SPEED_3G:
	//	((TamperNoWebServiceConfig*)pTamperConfig)->speedType = SPEED_3G;
	//	break;
	//case SPEED_4G:
	//	((TamperNoWebServiceConfig*)pTamperConfig)->speedType = SPEED_4G;
	//	break;
	//case SPEED_LTE:
	//	((TamperNoWebServiceConfig*)pTamperConfig)->speedType = SPEED_LTE;
	//	break;
	//case SPEED_MAX:
	//default:
	//	((TamperNoWebServiceConfig*)pTamperConfig)->speedType = SPEED_MAX;
	//	break;
	//}
}
