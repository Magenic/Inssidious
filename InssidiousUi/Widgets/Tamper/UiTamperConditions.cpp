#include "UiTamperConditions.h"
#include <ctime>

UiTamperConditions::UiTamperConditions(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = static_cast<void*>(new TamperConditionsConfig{0, 0, 0, 0});


	lossSpinBox = new QSpinBox();
	lossSpinBox->setRange(0, 100);
	lossSpinBox->setPrefix(lossText);
	lossSpinBox->setSuffix("%");
	lossSpinBox->setSingleStep(5);
	lossSpinBox->setFixedSize(66, 22);
	lossSpinBox->setStyleSheet(spinBoxStyleSheet);
	lossSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	delaySpinBox = new QSpinBox();
	delaySpinBox->setRange(0, 100);
	delaySpinBox->setPrefix(delayText);
	delaySpinBox->setSuffix("%");
	delaySpinBox->setSingleStep(5);
	delaySpinBox->setFixedSize(66, 22);
	delaySpinBox->setStyleSheet(spinBoxStyleSheet);
	delaySpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	junkSpinBox = new QSpinBox();
	junkSpinBox->setRange(0, 100);
	junkSpinBox->setPrefix(junkText);
	junkSpinBox->setSuffix("%");
	junkSpinBox->setSingleStep(5);
	junkSpinBox->setFixedSize(66, 22);
	junkSpinBox->setStyleSheet(spinBoxStyleSheet);
	junkSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	tcpResetSpinBox = new QSpinBox();
	tcpResetSpinBox->setRange(0, 100);
	tcpResetSpinBox->setPrefix(tcpResetText);
	tcpResetSpinBox->setSuffix("%");
	tcpResetSpinBox->setSingleStep(1);
	tcpResetSpinBox->setFixedSize(66, 22);
	tcpResetSpinBox->setStyleSheet(spinBoxStyleSheet);
	tcpResetSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	randomizeConditions = new QPushButton();
	randomizeConditions->setStyleSheet(buttonStyleSheet);
	randomizeConditions->setText("Randomize Conditions");
	randomizeConditions->setFont(moduleTextFont);
	randomizeConditions->setFixedSize(130, 30);
	randomizeConditions->setContentsMargins(0, 0, 0, 0);

	spinboxChildLayout = new QGridLayout();
	spinboxChildLayout->setSpacing(4);
	spinboxChildLayout->addWidget(lossSpinBox, 0, 0, Qt::AlignCenter);
	spinboxChildLayout->addWidget(junkSpinBox, 0, 1, Qt::AlignCenter);
	spinboxChildLayout->addWidget(delaySpinBox, 1, 0, Qt::AlignCenter);
	spinboxChildLayout->addWidget(tcpResetSpinBox, 1, 1, Qt::AlignCenter);

	conditionsLayout = new QGridLayout();
	conditionsLayout->setHorizontalSpacing(20);
	conditionsLayout->addWidget(randomizeConditions, 0, 1, 2, 1, Qt::AlignVCenter | Qt::AlignRight);	
	conditionsLayout->addItem(spinboxChildLayout, 0, 2, 1, 1, Qt::AlignCenter);

	lossSpinBox->setDisabled(true);
	delaySpinBox->setDisabled(true);
	junkSpinBox->setDisabled(true);
	tcpResetSpinBox->setDisabled(true);

	randomizeConditions->setDisabled(true);


	connect(randomizeConditions, &QPushButton::clicked, this, &UiTamperConditions::onRandomizeConditionsClicked);
	connect(lossSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onLossSpinBoxChange);
	connect(junkSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onJunkSpinBoxChange);
	connect(delaySpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onDelaySpinBoxChange);
	connect(tcpResetSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onResetSpinBoxChange);

	moduleDescriptionLabel->setContentsMargins(0, 6, 0, 12);
	moduleLayout->addLayout(conditionsLayout);
}


void UiTamperConditions::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */
		
		lossSpinBox->setEnabled(true);
		delaySpinBox->setEnabled(true);
		junkSpinBox->setEnabled(true);
		tcpResetSpinBox->setEnabled(true);

		randomizeConditions->setEnabled(true);
		onRandomizeConditionsClicked();


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);


		/* Clear and disable all buttons */

		lossSpinBox->setValue(0);
		delaySpinBox->setValue(0);
		junkSpinBox->setValue(0);
		tcpResetSpinBox->setValue(0);

		lossSpinBox->setDisabled(true);
		delaySpinBox->setDisabled(true);
		junkSpinBox->setDisabled(true);
		tcpResetSpinBox->setDisabled(true);

		randomizeConditions->setDisabled(true);

		/* Notify core to stop */

		emit tamperStop(this);

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
	static_cast<TamperConditionsConfig*>(pTamperConfig)->chanceLoss = value;
}

void UiTamperConditions::onJunkSpinBoxChange(int value)
{
	static_cast<TamperConditionsConfig*>(pTamperConfig)->chanceCorrupt = value;
}

void UiTamperConditions::onDelaySpinBoxChange(int value)
{
	static_cast<TamperConditionsConfig*>(pTamperConfig)->chanceDelay = value;
}

void UiTamperConditions::onResetSpinBoxChange(int value)
{
	static_cast<TamperConditionsConfig*>(pTamperConfig)->chanceReset = value;
}
