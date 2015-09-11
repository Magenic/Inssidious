#include "TamperWidget.h"

TamperWidget::TamperWidget(QWidget *parent)
	: QWidget(parent)
{
	/* Initialize the Tamper Widget Container */

	this->setAutoFillBackground(true);
	containerPalette.setBrush(QPalette::Background, QColor(234, 237, 242));
	this->setPalette(containerPalette);
	this->setGeometry(1 /* in */, 100 /* down */, 798 /* width */, 539 /* height */);

	this->tamperGridLayout = new QGridLayout();
	this->tamperGridLayout->setContentsMargins(12, 12, 12, 12);
	this->tamperGridLayout->setSpacing(12);
	this->setLayout(tamperGridLayout);


	/* Create the tamper module widgets */

	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		tamperModule[i] = UiTamperModule::makeUiTamperModule(this, TamperType(i));
		tamperModule[i]->setParent(this);
		connect(this->tamperModule[i], &UiTamperModule::tamperStart, this, &TamperWidget::onTamperModuleStart);
		connect(this->tamperModule[i], &UiTamperModule::tamperStop, this, &TamperWidget::onTamperModuleStop);
	}



	/* Add them to the grid layout */

	tamperGridLayout->addWidget(this->tamperModule[SPEED], 0, 0);
	tamperGridLayout->addWidget(this->tamperModule[CONDITIONS], 1, 0);
	tamperGridLayout->addWidget(this->tamperModule[FIREWALL], 2, 0);
	tamperGridLayout->addWidget(this->tamperModule[DAMAGE], 3, 0);

	tamperGridLayout->addWidget(this->tamperModule[NO_INTERNET], 0, 1);
	tamperGridLayout->addWidget(this->tamperModule[NO_SERVER], 1, 1);
	tamperGridLayout->addWidget(this->tamperModule[NO_WEB_CONTENT], 2, 1);
	tamperGridLayout->addWidget(this->tamperModule[WEBSERVICE_FAILURES], 3, 1);


}

TamperWidget::~TamperWidget()
{

}

void TamperWidget::setImage(QPixmap deviceImage)
{
	
	return;
}


void TamperWidget::onTamperModuleStart(UiTamperModule* signaled, void * pTamperConfig)
{
	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		if (tamperModule[i] == signaled)
		{
			emit tamperStart(this, TamperType(i), pTamperConfig);
			return;
		}
	}
}

void TamperWidget::onTamperModuleStop(UiTamperModule* signaled)
{
	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		if (tamperModule[i] == signaled)
		{
			emit tamperStop(this, TamperType(i));
			return;
		}
	}
}