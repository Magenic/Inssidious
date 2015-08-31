#include "UiTamperSpeed.h"

UiTamperSpeed::UiTamperSpeed(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)(new volatile short(0));

	speedDescriptionLabel = new QLabel();
	speedDescriptionLabel->setText(speedDescriptionText);
	speedDescriptionLabel->setContentsMargins(0, 6, 0, 20);
	speedDescriptionLabel->setAlignment(Qt::AlignHCenter);
	speedDescriptionLabel->setFont(moduleDescriptionFont);
	speedDescriptionLabel->setPalette(moduleTextPaletteInactive);

	buttonLeft = new QPushButton();
	buttonMiddle1 = new QPushButton();
	buttonMiddle2 = new QPushButton();
	buttonRight = new QPushButton();

	buttonLeft->setStyleSheet(buttonLeftStyleSheet);
	buttonMiddle1->setStyleSheet(buttonMiddleStyleSheet);
	buttonMiddle2->setStyleSheet(buttonMiddleStyleSheet);
	buttonRight->setStyleSheet(buttonRightStyleSheet);

	buttonLeft->setText("Edge");
	buttonMiddle1->setText("3G");
	buttonMiddle2->setText("4G");
	buttonRight->setText("LTE");

	buttonLeft->setFixedSize(53,26);
	buttonMiddle1->setFixedSize(53, 26);
	buttonMiddle2->setFixedSize(53, 26);
	buttonRight->setFixedSize(53, 26);

	buttonLeft->setCheckable(true);
	buttonMiddle1->setCheckable(true);
	buttonMiddle2->setCheckable(true);
	buttonRight->setCheckable(true);

	buttonLeft->setDisabled(true);
	buttonMiddle1->setDisabled(true);
	buttonMiddle2->setDisabled(true);
	buttonRight->setDisabled(true);

	speedLayout = new QGridLayout();
	speedLayout->setAlignment(Qt::AlignHCenter);
	speedLayout->setSpacing(0);
	
	speedLayout->addWidget(speedDescriptionLabel, 0, 0, 1, 4);

	speedLayout->addWidget(buttonLeft, 1, 0);
	speedLayout->addWidget(buttonMiddle1, 1, 1);
	speedLayout->addWidget(buttonMiddle2, 1, 2);
	speedLayout->addWidget(buttonRight, 1, 3);


	moduleLayout->addLayout(speedLayout);
}

UiTamperSpeed::~UiTamperSpeed()
{

}

void UiTamperSpeed::toggleState(bool active)
{
	if (active)
	{
		speedDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		buttonLeft->setEnabled(true);
		buttonMiddle1->setEnabled(true);
		buttonMiddle2->setEnabled(true);
		buttonRight->setEnabled(true);
	}
	else
	{
		speedDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		buttonLeft->setDisabled(true);
		buttonMiddle1->setDisabled(true);
		buttonMiddle2->setDisabled(true);
		buttonRight->setDisabled(true);
	}
}
