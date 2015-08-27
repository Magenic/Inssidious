#include "UiTamperSpeed.h"

UiTamperSpeed::UiTamperSpeed(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)(new volatile short(5));

	speedSlider = new QSlider(Qt::Horizontal, this);


	connect(speedSlider, &QSlider::valueChanged, this, &UiTamperSpeed::onSpeedSliderChanged);

	speedSlider->setRange(1, 5);
	speedSlider->setPageStep(1);
	speedSlider->setTickPosition(QSlider::TicksBelow);
	speedSlider->setMinimum(1);
	speedSlider->setMaximum(5);

	sliderTextLabel = new QLabel();
	sliderTextLabel->setPalette(moduleTextPaletteInactive);
	sliderTextLabel->setText(sliderString);

	speedLayout = new QGridLayout();
	speedLayout->setContentsMargins(0, 0, 0, 0);
	speedLayout->setSpacing(0);
	speedLayout->addItem(new QSpacerItem(12,0), 0, 0);
	speedLayout->addWidget(speedSlider, 0, 1);
	speedLayout->addItem(new QSpacerItem(12,0), 0, 2);

	speedLayout->addWidget(sliderTextLabel, 1, 0, 1, 4);
	
	moduleLayout->addLayout(speedLayout);
}

UiTamperSpeed::~UiTamperSpeed()
{

}

void UiTamperSpeed::onSpeedSliderChanged(int value)
{
	switch (value)
	{
	case SPEED_EDGE:
		*(short*)pTamperConfig = 1;
		break;
	case SPEED_3G:
		*(short*)pTamperConfig = 2;
		break;
	case SPEED_4G:
		*(short*)pTamperConfig = 3;
		break;
	case SPEED_LTE:
		*(short*)pTamperConfig = 4;
		break;
	case SPEED_MAX:
		*(short*)pTamperConfig = 5;
		break;
	default:
		break;
	}
}
