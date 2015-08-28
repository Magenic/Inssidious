#include "UiTamperDelay.h"

UiTamperDelay::UiTamperDelay(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	
	qButtonGroup = new QButtonGroup(this);
	qButtonGroup->setExclusive(true);

	bLow = new QPushButton("Low", this);
	bMid = new QPushButton("Mid", this);
	bHigh = new QPushButton("High", this);

	bLow->setCheckable(true);
	bMid->setCheckable(true);
	bHigh->setCheckable(true);

	qButtonGroup->addButton(bLow, 1);
	qButtonGroup->addButton(bMid, 2);
	qButtonGroup->addButton(bHigh, 3);

	delayLayout = new QGridLayout(this);
	delayLayout->addWidget(bLow, 0, 0);
	delayLayout->addWidget(bMid, 0, 1);
	delayLayout->addWidget(bHigh, 0, 2);

	moduleLayout->addLayout(delayLayout);
}

UiTamperDelay::~UiTamperDelay()
{

}
