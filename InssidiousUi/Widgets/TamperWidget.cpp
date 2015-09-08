#include "TamperWidget.h"

TamperWidget::TamperWidget(QWidget *parent)
	: QWidget(parent)
{
	/* Initialize the Tamper Widget Container */

	this->setAutoFillBackground(true);
	containerPalette.setBrush(QPalette::Background, QColor(234, 237, 242)/*QBrush(backgroundGrid)*/);
	this->setPalette(containerPalette);
	this->setGeometry(1 /* in */, 100 /* down */, 798 /* width */, 539 /* height */);

	this->tamperGridLayout = new QGridLayout();
	//this->tamperGridLayout->setContentsMargins(20, 10, 20, 8);
	//this->tamperGridLayout->setSpacing(20);
	this->tamperGridLayout->setContentsMargins(12, 12, 12, 12);
	this->tamperGridLayout->setSpacing(12);
	this->setLayout(tamperGridLayout);


	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		tamperModule[i] = UiTamperModule::makeUiTamperModule(this, TamperType(i));
		tamperModule[i]->setParent(this);
		connect(this->tamperModule[i], &UiTamperModule::tamperButtonClicked, this, &TamperWidget::onTamperModuleClicked);
	}




	tamperGridLayout->addWidget(this->tamperModule[SPEED], 0, 0);
	tamperGridLayout->addWidget(this->tamperModule[CONDITIONS], 1, 0);
	tamperGridLayout->addWidget(this->tamperModule[FIREWALL], 2, 0);

	tamperGridLayout->addWidget(this->tamperModule[NO_INTERNET], 0, 1);
	tamperGridLayout->addWidget(this->tamperModule[NO_SERVER], 1, 1);
	tamperGridLayout->addWidget(this->tamperModule[NO_WEBSERVICE], 2, 1);





	QWidget* tempHTTPComingSoon = new QWidget();
	tempHTTPComingSoon->setFixedWidth(798);
	tempHTTPComingSoon->setFixedHeight(124);
	tempHTTPComingSoon->setAutoFillBackground(true);
	QPalette comingSoonPalette;
	comingSoonPalette.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/ComingSoon.png")));
	tempHTTPComingSoon->setPalette(comingSoonPalette);


	tamperGridLayout->addWidget(tempHTTPComingSoon, 3, 0, 1, 2);
	//tamperGridLayout->addWidget(this->tamperModule[HTTP_TIME_OUT], 2, 0);
	//tamperGridLayout->addWidget(this->tamperModule[HTTP_UNEXPECTED_RESPONSE], 2, 1);
	//tamperGridLayout->addWidget(this->tamperModule[HTTP_CORRUPTED_RESPONSE], 2, 2);

}

TamperWidget::~TamperWidget()
{

}

void TamperWidget::setImage(QPixmap deviceImage)
{
	
	return;
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