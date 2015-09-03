#include "UiTamperConditions.h"
#include <ctime>

UiTamperConditions::UiTamperConditions(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperConditionsConfig{0, 0, 0, 0};

	conditionsDescriptionLabel = new QLabel();
	conditionsDescriptionLabel->setText(conditionsDescriptionText);
	conditionsDescriptionLabel->setContentsMargins(0, 6, 0, 14);
	conditionsDescriptionLabel->setAlignment(Qt::AlignHCenter);
	conditionsDescriptionLabel->setFont(moduleDescriptionFont);
	conditionsDescriptionLabel->setPalette(moduleTextPaletteInactive);

	lossSpinBox = new QSpinBox();
	lossSpinBox->setRange(0, 100);
	lossSpinBox->setPrefix(lossText);
	lossSpinBox->setSuffix("%");
	lossSpinBox->setSingleStep(5);
	lossSpinBox->setFixedWidth(62);
	lossSpinBox->setDisabled(true);
	lossSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	delaySpinBox = new QSpinBox();
	delaySpinBox->setRange(0, 100);
	delaySpinBox->setPrefix(delayText);
	delaySpinBox->setSuffix("%");
	delaySpinBox->setSingleStep(5);
	delaySpinBox->setFixedWidth(65);
	delaySpinBox->setDisabled(true);
	delaySpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	junkSpinBox = new QSpinBox();
	junkSpinBox->setRange(0, 100);
	junkSpinBox->setPrefix(junkText);
	junkSpinBox->setSuffix("%");
	junkSpinBox->setSingleStep(5);
	junkSpinBox->setFixedWidth(62);
	junkSpinBox->setDisabled(true);
	junkSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	tcpResetSpinBox = new QSpinBox();
	tcpResetSpinBox->setRange(0, 100);
	tcpResetSpinBox->setPrefix(tcpResetText);
	tcpResetSpinBox->setSuffix("%");
	tcpResetSpinBox->setSingleStep(1);
	tcpResetSpinBox->setFixedWidth(65);
	tcpResetSpinBox->setDisabled(true);
	tcpResetSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	randomizeConditions = new QPushButton();
	randomizeConditions->setStyleSheet(buttonStyleSheet);
	randomizeConditions->setText("Randomize\nConditions");
	randomizeConditions->setFont(moduleDescriptionFont);
	randomizeConditions->setFixedSize(70, 40);
	randomizeConditions->setDisabled(true);
	randomizeConditions->setContentsMargins(0, 0, 0, 0);
	
	spinboxChildLayout = new QGridLayout();
	spinboxChildLayout->setSpacing(0);
	spinboxChildLayout->addWidget(lossSpinBox, 0, 0);
	spinboxChildLayout->addWidget(junkSpinBox, 1, 0);
	spinboxChildLayout->addWidget(delaySpinBox, 0, 1);
	spinboxChildLayout->addWidget(tcpResetSpinBox, 1, 1);

	conditionsLayout = new QGridLayout();
	conditionsLayout->setSpacing(0);
	conditionsLayout->setContentsMargins(12, 0, 10, 0);

	conditionsLayout->addWidget(conditionsDescriptionLabel, 0, 0, 1, 2);
	conditionsLayout->addWidget(randomizeConditions, 1, 0);
	conditionsLayout->addLayout(spinboxChildLayout, 1, 1);


	connect(randomizeConditions, &QPushButton::clicked, this, &UiTamperConditions::onRandomizeConditionsClicked);
	connect(lossSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onLossSpinBoxChange);
	connect(junkSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onJunkSpinBoxChange);
	connect(delaySpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onDelaySpinBoxChange);
	connect(tcpResetSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onResetSpinBoxChange);


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
		
		randomizeConditions->setEnabled(true);
		lossSpinBox->setEnabled(true);
		delaySpinBox->setEnabled(true);
		junkSpinBox->setEnabled(true);
		tcpResetSpinBox->setEnabled(true);
	}
	else
	{
		conditionsDescriptionLabel->setPalette(moduleTextPaletteInactive);

		randomizeConditions->setDisabled(true);
		lossSpinBox->setDisabled(true);
		delaySpinBox->setDisabled(true);
		junkSpinBox->setDisabled(true);
		tcpResetSpinBox->setDisabled(true);
	}
}


void UiTamperConditions::onRandomizeConditionsClicked()
{
	srand(time(nullptr));
	lossSpinBox->setValue(rand() % 30);
	junkSpinBox->setValue(rand() % 30);
	delaySpinBox->setValue(rand() % 100);
	tcpResetSpinBox->setValue(rand() % 20);
}

void UiTamperConditions::onLossSpinBoxChange(int value)
{
	((TamperConditionsConfig*)pTamperConfig)->chanceLoss = value;
}

void UiTamperConditions::onJunkSpinBoxChange(int value)
{
	((TamperConditionsConfig*)pTamperConfig)->chanceCorrupt = value;
}

void UiTamperConditions::onDelaySpinBoxChange(int value)
{
	((TamperConditionsConfig*)pTamperConfig)->chanceDelay = value;
}

void UiTamperConditions::onResetSpinBoxChange(int value)
{
	((TamperConditionsConfig*)pTamperConfig)->chanceReset = value;
}
