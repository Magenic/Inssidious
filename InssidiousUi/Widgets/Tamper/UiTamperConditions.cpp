#include "UiTamperConditions.h"

UiTamperConditions::UiTamperConditions(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{

	conditionsDescriptionLabel = new QLabel();
	conditionsDescriptionLabel->setText(conditionsDescriptionText);
	conditionsDescriptionLabel->setContentsMargins(0, 6, 0, 14);
	conditionsDescriptionLabel->setAlignment(Qt::AlignHCenter);
	conditionsDescriptionLabel->setFont(moduleDescriptionFont);
	conditionsDescriptionLabel->setPalette(moduleTextPaletteInactive);

	
	lossLabel = new QLabel("");
	lossLabel->setText(lossText);
	lossLabel->setFixedHeight(26);
	lossLabel->setFont(moduleDescriptionFont);
	lossLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	lossLabel->setPalette(this->moduleTextPaletteInactive);
	lossSpinBox = new QSpinBox();
	lossSpinBox->setRange(0, 100);
	lossSpinBox->setSuffix("%");
	lossSpinBox->setSingleStep(5);
	lossSpinBox->setFixedWidth(46);
	lossSpinBox->setDisabled(true);

	delayLabel = new QLabel();
	delayLabel->setText(delayText);
	delayLabel->setFixedHeight(26);
	delayLabel->setFixedWidth(56);
	delayLabel->setFont(moduleDescriptionFont);
	delayLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	delayLabel->setPalette(this->moduleTextPaletteInactive);
	delaySpinBox = new QSpinBox();
	delaySpinBox->setRange(0, 100);
	delaySpinBox->setSuffix("%");
	delaySpinBox->setSingleStep(5);
	delaySpinBox->setFixedWidth(46);
	delaySpinBox->setDisabled(true);


	corruptionLabel = new QLabel();
	corruptionLabel->setText(corruptionText);
	corruptionLabel->setFixedHeight(26);
	corruptionLabel->setFont(moduleDescriptionFont);
	corruptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	corruptionLabel->setPalette(this->moduleTextPaletteInactive);
	corruptionSpinBox = new QSpinBox();
	corruptionSpinBox->setRange(0, 100);
	corruptionSpinBox->setSuffix("%");
	corruptionSpinBox->setSingleStep(5);
	corruptionSpinBox->setFixedWidth(46);
	corruptionSpinBox->setDisabled(true);

	tcpResetLabel = new QLabel();
	tcpResetLabel->setText(tcpResetText);
	tcpResetLabel->setFixedHeight(26);
	tcpResetLabel->setFixedWidth(56);
	tcpResetLabel->setFont(moduleDescriptionFont);
	tcpResetLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	tcpResetLabel->setPalette(this->moduleTextPaletteInactive);
	tcpResetSpinBox = new QSpinBox();
	tcpResetSpinBox->setRange(0, 100);
	tcpResetSpinBox->setSuffix("%");
	tcpResetSpinBox->setSingleStep(5);
	tcpResetSpinBox->setFixedWidth(46);
	tcpResetSpinBox->setDisabled(true);


	conditionsLayout = new QGridLayout();
	conditionsLayout->setSpacing(0);
	conditionsLayout->addWidget(conditionsDescriptionLabel, 0, 0, 1, 4);

	conditionsLayout->addWidget(lossLabel, 1, 0);
	conditionsLayout->addWidget(lossSpinBox, 1, 1);
	conditionsLayout->addWidget(corruptionLabel, 2, 0);
	conditionsLayout->addWidget(corruptionSpinBox, 2, 1);

	conditionsLayout->addWidget(delayLabel, 1, 2);
	conditionsLayout->addWidget(delaySpinBox, 1, 3, Qt::AlignLeft);
	conditionsLayout->addWidget(tcpResetLabel, 2, 2);
	conditionsLayout->addWidget(tcpResetSpinBox, 2, 3, Qt::AlignLeft);



	moduleLayout->addLayout(conditionsLayout);
}

UiTamperConditions::~UiTamperConditions()
{

}
void UiTamperConditions::toggleState(bool active)
{
	if (active)
	{
		conditionsDescriptionLabel->setPalette(moduleTextPaletteActive);

		lossLabel->setPalette(this->moduleTextPaletteActive);
		delayLabel->setPalette(this->moduleTextPaletteActive);
		corruptionLabel->setPalette(this->moduleTextPaletteActive);
		tcpResetLabel->setPalette(this->moduleTextPaletteActive);

		lossSpinBox->setEnabled(true);
		delaySpinBox->setEnabled(true);
		corruptionSpinBox->setEnabled(true);
		tcpResetSpinBox->setEnabled(true);
	}
	else
	{
		conditionsDescriptionLabel->setPalette(moduleTextPaletteInactive);

		lossLabel->setPalette(this->moduleTextPaletteInactive);
		delayLabel->setPalette(this->moduleTextPaletteInactive);
		corruptionLabel->setPalette(this->moduleTextPaletteInactive);
		tcpResetLabel->setPalette(this->moduleTextPaletteInactive);

		lossSpinBox->setDisabled(true);
		delaySpinBox->setDisabled(true);
		corruptionSpinBox->setDisabled(true);
		tcpResetSpinBox->setDisabled(true);
	}
}
