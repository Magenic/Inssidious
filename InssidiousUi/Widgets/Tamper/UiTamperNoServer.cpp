#include "UiTamperNoServer.h"

UiTamperNoServer::UiTamperNoServer(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{

	noServerDescriptionLabel = new QLabel();
	noServerDescriptionLabel->setText(noServerDescriptionText);
	noServerDescriptionLabel->setFixedHeight(12);
	noServerDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noServerDescriptionLabel->setFont(moduleDescriptionFont);
	noServerDescriptionLabel->setPalette(moduleTextPaletteInactive);

	noServerButton = new QPushButton();
	noServerButton->setCheckable(true);
	noServerButton->setStyleSheet(buttonDoubleWideStyleSheet);
	noServerButton->setFixedSize(120, 24);
	noServerButton->setText("Block Servers");
	noServerButton->setDisabled(true);

	configServersDescriptionLabel = new QLabel();
	configServersDescriptionLabel->setText(configServersDescriptionText);
	configServersDescriptionLabel->setFixedHeight(30);
	configServersDescriptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	configServersDescriptionLabel->setFont(moduleDescriptionFont);
	configServersDescriptionLabel->setPalette(moduleTextPaletteInactive);
				
	configServersButton = new QPushButton();
	configServersButton->setCheckable(true);
	configServersButton->setStyleSheet(buttonMiddleStyleSheet);
	configServersButton->setFixedSize(16, 16);
	configServersButton->setText("");
	configServersButton->setDisabled(true);


	noServerLayout = new QGridLayout();
	noServerLayout->setAlignment(Qt::AlignHCenter);
	noServerLayout->setContentsMargins(10, 0, 10, 0);
	noServerLayout->addItem(new QSpacerItem(0, 6), 0, 0);
	noServerLayout->addWidget(noServerDescriptionLabel, 1, 0, 1, 3);
	noServerLayout->addItem(new QSpacerItem(0, 12), 2, 0);
	noServerLayout->addWidget(noServerButton, 3, 0, 1, 3, Qt::AlignHCenter);
	noServerLayout->addItem(new QSpacerItem(0, 10), 4, 0);
	noServerLayout->addWidget(configServersDescriptionLabel, 5, 0, 1, 2);
	noServerLayout->addWidget(configServersButton, 5, 2);

	moduleLayout->addLayout(noServerLayout);
}

UiTamperNoServer::~UiTamperNoServer()
{

}
void UiTamperNoServer::toggleState(bool active)
{
	if (active)
	{
		noServerDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		configServersDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		noServerButton->setEnabled(true);
		configServersButton->setEnabled(true);
	}
	else
	{
		noServerDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		configServersDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		noServerButton->setDisabled(true);
		configServersButton->setDisabled(true);
	}
}
