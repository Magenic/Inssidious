#include "UiTamperDamage.h"
#include <ctime>

UiTamperDamage::UiTamperDamage(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	srand(time(nullptr));
	pTamperConfig = static_cast<void*>(new TamperDamageConfig{ false });


	damageSpinBox = new QSpinBox();
	damageSpinBox->setRange(0, 100);
	damageSpinBox->setPrefix(damageText);
	damageSpinBox->setSuffix("%");
	damageSpinBox->setSingleStep(5);
	damageSpinBox->setFixedSize(108, 22);
	damageSpinBox->setStyleSheet(spinBoxStyleSheet);
	damageSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	tcpCloseSpinBox = new QSpinBox();
	tcpCloseSpinBox->setRange(0, 100);
	tcpCloseSpinBox->setPrefix(tcpCloseText);
	tcpCloseSpinBox->setSuffix("%");
	tcpCloseSpinBox->setSingleStep(5);
	tcpCloseSpinBox->setFixedSize(108, 22);
	tcpCloseSpinBox->setStyleSheet(spinBoxStyleSheet);
	tcpCloseSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	randomizeConditions = new QPushButton();
	randomizeConditions->setStyleSheet(buttonStyleSheet);
	randomizeConditions->setText("Randomize Conditions");
	randomizeConditions->setFont(moduleTextFont);
	randomizeConditions->setFixedSize(130, 30);
	randomizeConditions->setContentsMargins(0, 0, 0, 0);

	spinboxChildLayout = new QGridLayout();
	spinboxChildLayout->setSpacing(4);
	spinboxChildLayout->addWidget(damageSpinBox, 0, 0, Qt::AlignCenter);
	spinboxChildLayout->addWidget(tcpCloseSpinBox, 1, 0, Qt::AlignCenter);

	damageLayout = new QGridLayout();
	damageLayout->setHorizontalSpacing(20);
	damageLayout->addWidget(randomizeConditions, 0, 1, 2, 1, Qt::AlignVCenter | Qt::AlignRight);
	damageLayout->addItem(spinboxChildLayout, 0, 2, 1, 1, Qt::AlignCenter);


	damageSpinBox->setDisabled(true);
	tcpCloseSpinBox->setDisabled(true);
	randomizeConditions->setDisabled(true);


	connect(randomizeConditions, &QPushButton::clicked, this, &UiTamperDamage::onRandomizeConditionsClicked);
	connect(damageSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperDamage::onDamageSpinBoxChange);
	connect(tcpCloseSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperDamage::onTCPCloseSpinBoxChange);


	moduleDescriptionLabel->setContentsMargins(0, 6, 0, 12);
	moduleLayout->addLayout(damageLayout);
}


void UiTamperDamage::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		damageSpinBox->setEnabled(true);
		//tcpCloseSpinBox->setEnabled(true);

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

		damageSpinBox->setValue(0);
		tcpCloseSpinBox->setValue(0);

		damageSpinBox->setDisabled(true);
		tcpCloseSpinBox->setDisabled(true);
		randomizeConditions->setDisabled(true);

		/* Notify core to stop */

		emit tamperStop(this);

	}
}


void UiTamperDamage::onRandomizeConditionsClicked()
{
	damageSpinBox->setValue(rand() % 30);
	//tcpCloseSpinBox->setValue(rand() % 15);
}

void UiTamperDamage::onDamageSpinBoxChange(int value)
{
	static_cast<TamperDamageConfig*>(pTamperConfig)->chanceDamage = value;
}

void UiTamperDamage::onTCPCloseSpinBoxChange(int value)
{
	static_cast<TamperDamageConfig*>(pTamperConfig)->chanceClose = value;
}