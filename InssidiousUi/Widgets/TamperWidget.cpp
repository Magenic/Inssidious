#include "TamperWidget.h"

TamperWidget::TamperWidget(QWidget *parent)
	: QWidget(parent)
{
	/* Initialize the Tamper Widget Container */

	this->setAutoFillBackground(true);
	twContainerPalette.setBrush(QPalette::Background,		//Set a background image for the devices present palette
		QBrush(tcBackgroundImageDevicesPresent));				//With the tab container area background image
	this->setPalette(twContainerPalette);
	this->setGeometry(10 /* in */, 108 /* down */, 780 /* width */, 480 /* height */);

	tamperGridLayout = new QGridLayout();
	this->setLayout(tamperGridLayout);
	this->tamperGridLayout->setContentsMargins(20, 10, 20, 8);
	this->tamperGridLayout->setSpacing(20);


	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		tamperModule[i] = UiTamperModule::makeUiTamperModule(this, TamperType(i));
		tamperModule[i]->setParent(this);
		connect(this->tamperModule[i], &UiTamperModule::tamperButtonClicked, this, &TamperWidget::onTamperModuleClicked);
	}



	/* Add the Tamper Types to the appropriate class layouts */

	tamperGridLayout->addWidget(this->tamperModule[SPEED], 0, 0);
	tamperGridLayout->addWidget(this->tamperModule[CONDITIONS], 0, 1);
	tamperGridLayout->addWidget(this->tamperModule[FIREWALL], 0, 2);

	tamperGridLayout->addWidget(this->tamperModule[NO_INTERNET], 1, 0);
	tamperGridLayout->addWidget(this->tamperModule[NO_SERVER], 1, 1);
	tamperGridLayout->addWidget(this->tamperModule[NO_WEBSERVICE], 1, 2);

	QWidget* tempHTTPComingSoon = new QWidget();
	tempHTTPComingSoon->setFixedWidth(738);
	tempHTTPComingSoon->setFixedHeight(130);
	tempHTTPComingSoon->setAutoFillBackground(true);
	QPalette comingSoonPalette;
	comingSoonPalette.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/ComingSoon.png")));
	tempHTTPComingSoon->setPalette(comingSoonPalette);

	tamperGridLayout->addWidget(tempHTTPComingSoon, 2, 0, 1, 3);
	//tamperGridLayout->addWidget(this->tamperModule[HTTP_TIME_OUT], 2, 0);
	//tamperGridLayout->addWidget(this->tamperModule[HTTP_UNEXPECTED_RESPONSE], 2, 1);
	//tamperGridLayout->addWidget(this->tamperModule[HTTP_CORRUPTED_RESPONSE], 2, 2);

}

TamperWidget::~TamperWidget()
{

}

void TamperWidget::onTamperModuleClicked(UiTamperModule* signaled, void * pTamperConfig)
{
	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		if (tamperModule[i] == signaled)
		{
			if (tamperModule[i]->selected)
			{
				emit tamperStop(this, TamperType(i));
				tamperModule[i]->unselect();
			}
			else
			{
				emit tamperStart(this, TamperType(i), pTamperConfig);
				tamperModule[i]->select();
			}
		}
	}
}