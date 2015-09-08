#include "UiTamperNoServer.h"

#include "ConfigureServersDialog.h"

UiTamperNoServer::UiTamperNoServer(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperNoServerConfig{ false };

	noServerDescriptionLabel = new QLabel();
	noServerDescriptionLabel->setText(noServerDescriptionText);
	noServerDescriptionLabel->setContentsMargins(0, 6, 0, 20);
	noServerDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noServerDescriptionLabel->setFont(moduleDescriptionFont);
	noServerDescriptionLabel->setPalette(moduleTextPaletteInactive);

	noServerButton = new QPushButton();
	noServerButton->setCheckable(true);
	noServerButton->setStyleSheet(buttonStyleSheet);
	noServerButton->setFixedSize(130, 30);
	noServerButton->setText(blockedServerTextFront + QString::number(blockedServersCount) + blockedServerTextBack);


	configServersButton = new QPushButton();
	configServersButton->setStyleSheet(buttonStyleSheet);
	configServersButton->setFixedSize(130, 30);
	configServersButton->setText("Configure Block List");


	noServerLayout = new QGridLayout();
	noServerLayout->setHorizontalSpacing(20);
	noServerLayout->setAlignment(Qt::AlignHCenter);
	noServerLayout->setContentsMargins(10, 0, 10, 0);
	noServerLayout->addWidget(noServerDescriptionLabel, 1, 0, 1, 2);
	noServerLayout->addWidget(noServerButton, 2, 0, Qt::AlignHCenter);
	noServerLayout->addWidget(configServersButton, 2, 1, Qt::AlignHCenter);



	connect(configServersButton, &QPushButton::clicked, this, &UiTamperNoServer::onConfigureServers);

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
		noServerButton->setEnabled(true);
		configServersButton->setEnabled(true);
	}
	else
	{
		noServerDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		noServerButton->setDisabled(true);
		configServersButton->setDisabled(true);
	}
}

void UiTamperNoServer::onConfigureServers()
{
	
	QList<QString> stringList;
	QPoint global = this->mapToGlobal(rect().center());
	ConfigureServersDialog* dialog = new ConfigureServersDialog(global, &stringList);
	dialog->exec();
	delete dialog;

	//if (stringList.count() > 0)
	//{
	//	//TODO: get this to the tamper module	

	//	blockedServersCount = stringList.count();
	//	blockedServersComboBox->clear();
	//	blockedServersComboBox->addItem(blockedServerFirstItemText + QString::number(blockedServersCount));

	//	QList<_Uint32t> ipList;

	//	for (int i = 0; i < stringList.count(); i++)
	//	{

	//		blockedServersComboBox->addItem(stringList[i]);

	//		_Uint32t ipAsInt = 0;
	//		InetPton(AF_INET, (const wchar_t*)stringList[i].split(" ").first().utf16(), &ipAsInt);

	//		ipList.append(ipAsInt);
	//	}

	//}
}
