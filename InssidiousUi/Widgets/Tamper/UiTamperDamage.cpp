#include "UiTamperDamage.h"
#include <ctime>

UiTamperDamage::UiTamperDamage(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{

	pTamperConfig = (void*)new TamperDamageConfig{ false };


	damageSpinBox = new QSpinBox();
	damageSpinBox->setRange(0, 100);
	damageSpinBox->setPrefix(damageText);
	damageSpinBox->setSuffix("%");
	damageSpinBox->setSingleStep(5);
	damageSpinBox->setFixedSize(82, 24);
	damageSpinBox->setStyleSheet(spinBoxStyleSheet);
	damageSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	randomizeConditions = new QPushButton();
	randomizeConditions->setStyleSheet(buttonStyleSheet);
	randomizeConditions->setText("Randomize");
	randomizeConditions->setFont(moduleTextFont);
	randomizeConditions->setFixedSize(90, 30);
	randomizeConditions->setContentsMargins(0, 0, 0, 0);

	damageLayout = new QGridLayout();
	damageLayout->setHorizontalSpacing(20);
	damageLayout->addWidget(randomizeConditions, 0, 0, Qt::AlignVCenter | Qt::AlignRight);
	damageLayout->addWidget(damageSpinBox, 0, 1, Qt::AlignVCenter | Qt::AlignLeft);

	damageSpinBox->setDisabled(true);
	randomizeConditions->setDisabled(true);


	connect(randomizeConditions, &QPushButton::clicked, this, &UiTamperDamage::onRandomizeConditionsClicked);
	connect(damageSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperDamage::onDamageSpinBoxChange);


	moduleLayout->addLayout(damageLayout);
}

UiTamperDamage::~UiTamperDamage()
{

}
void UiTamperDamage::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		damageSpinBox->setEnabled(true);

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

		damageSpinBox->setDisabled(true);
		randomizeConditions->setDisabled(true);

		/* Notify core to stop */

		emit tamperStop(this);

	}
}


void UiTamperDamage::onRandomizeConditionsClicked()
{
	srand(time(nullptr));
	damageSpinBox->setValue(rand() % 30);
}

void UiTamperDamage::onDamageSpinBoxChange(int value)
{
	((TamperDamageConfig*)pTamperConfig)->chanceDamage = value;
}