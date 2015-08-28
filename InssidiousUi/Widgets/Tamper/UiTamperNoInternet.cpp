#include "UiTamperNoInternet.h"

UiTamperNoInternet::UiTamperNoInternet(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	
	noInternetButton = new QPushButton();
	noInternetButton->setCheckable(true);

	noInternetLayout = new QGridLayout();
	noInternetLayout->addWidget(noInternetButton, 0, 0);

	moduleLayout->addLayout(noInternetLayout);
}

UiTamperNoInternet::~UiTamperNoInternet()
{

}
