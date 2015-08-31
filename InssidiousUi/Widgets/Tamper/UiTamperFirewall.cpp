#include "UiTamperFirewall.h"

UiTamperFirewall::UiTamperFirewall(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	firewallDescriptionLabel = new QLabel();
	firewallDescriptionLabel->setText(firewallDescriptionText);
	firewallDescriptionLabel->setFixedHeight(12);
	firewallDescriptionLabel->setAlignment(Qt::AlignHCenter);
	firewallDescriptionLabel->setFont(moduleDescriptionFont);
	firewallDescriptionLabel->setPalette(moduleTextPaletteInactive);


	httpDescriptionLabel = new QLabel();
	httpDescriptionLabel->setText(httpDescriptionText);
	httpDescriptionLabel->setFixedHeight(30);
	httpDescriptionLabel->setWordWrap(true);
	httpDescriptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	httpDescriptionLabel->setFont(moduleDescriptionFont);
	httpDescriptionLabel->setPalette(moduleTextPaletteInactive);

	httpButton = new QPushButton();
	httpsButton = new QPushButton();

	httpButton->setStyleSheet(buttonLeftStyleSheet);
	httpsButton->setStyleSheet(buttonRightStyleSheet);
	httpButton->setText("HTTP");
	httpsButton->setText("HTTPS");
	httpsButton->setText("HTTPS");
	httpButton->setFont(moduleDescriptionFont);
	httpsButton->setFont(moduleDescriptionFont);
	httpButton->setFixedSize(60, 24);
	httpsButton->setFixedSize(60, 24);
	httpButton->setCheckable(true);
	httpsButton->setCheckable(true);
	httpButton->setDisabled(true);
	httpsButton->setDisabled(true);


	filterDescriptionLabel = new QLabel();
	filterDescriptionLabel->setText(filterDescriptionText);
	filterDescriptionLabel->setFixedHeight(30);
	filterDescriptionLabel->setWordWrap(true);
	filterDescriptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	filterDescriptionLabel->setFont(moduleDescriptionFont);
	filterDescriptionLabel->setPalette(moduleTextPaletteInactive);

	filterButton = new QPushButton();
	filterButton->setStyleSheet(buttonDoubleWideStyleSheet);
	filterButton->setText("Block All Content");
	filterButton->setFont(moduleDescriptionFont);
	filterButton->setFixedSize(120, 24);
	filterButton->setCheckable(true);
	filterButton->setDisabled(true);



	firewallLayout = new QGridLayout();
	firewallLayout->setAlignment(Qt::AlignHCenter);
	firewallLayout->setSpacing(0);
	firewallLayout->addItem(new QSpacerItem(0, 6), 0, 0);
	firewallLayout->addWidget(firewallDescriptionLabel, 1, 0, 1, 3);
	firewallLayout->addItem(new QSpacerItem(0, 12), 2, 0);
	firewallLayout->addWidget(httpDescriptionLabel, 3, 0);
	firewallLayout->addWidget(httpButton, 3, 1, Qt::AlignCenter);
	firewallLayout->addWidget(httpsButton, 3, 2, Qt::AlignCenter);
	firewallLayout->addItem(new QSpacerItem(0, 2), 4, 0);
	firewallLayout->addWidget(filterDescriptionLabel, 5, 0);
	firewallLayout->addWidget(filterButton, 5, 1, 1, 2, Qt::AlignCenter);


	moduleLayout->addLayout(firewallLayout);
}

UiTamperFirewall::~UiTamperFirewall()
{

}

void UiTamperFirewall::toggleState(bool active)
{
	if (active)
	{
		firewallDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		httpDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		filterDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		httpButton->setEnabled(true);
		httpsButton->setEnabled(true);
		filterButton->setEnabled(true);
	}
	else
	{
		firewallDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		httpDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		filterDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		httpButton->setDisabled(true);
		httpsButton->setDisabled(true);
		filterButton->setDisabled(true);
	}
}
