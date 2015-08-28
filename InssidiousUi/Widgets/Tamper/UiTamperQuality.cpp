#include "UiTamperQuality.h"

UiTamperQuality::UiTamperQuality(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{

	
	lossLabel = new QLabel("Loss:");
	corruptionLabel = new QLabel("Corruption:");
	tcpResetLabel = new QLabel("TCP Reset:");

	lossSpinBox = new QSpinBox();
	lossSpinBox->setRange(0, 100);
	lossSpinBox->setSuffix("%");
	lossSpinBox->setSingleStep(5);

	corruptionSpinBox = new QSpinBox();
	corruptionSpinBox->setRange(0, 100);
	corruptionSpinBox->setSuffix("%");
	corruptionSpinBox->setSingleStep(5);

	tcpResetSpinBox = new QSpinBox();
	tcpResetSpinBox->setRange(0, 100);
	tcpResetSpinBox->setSuffix("%");
	tcpResetSpinBox->setSingleStep(5);


	qualityLayout = new QGridLayout(this);
	qualityLayout->addWidget(lossLabel, 0, 0);
	qualityLayout->addWidget(lossSpinBox, 0, 1);
	qualityLayout->addWidget(corruptionLabel, 0, 2);
	qualityLayout->addWidget(corruptionSpinBox, 0, 3);
	qualityLayout->addWidget(tcpResetLabel, 0, 4);
	qualityLayout->addWidget(tcpResetSpinBox, 0, 5);

	moduleLayout->addLayout(qualityLayout);
}

UiTamperQuality::~UiTamperQuality()
{

}
