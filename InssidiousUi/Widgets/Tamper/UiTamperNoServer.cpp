#include "UiTamperNoServer.h"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QAbstractItemView>
#include "ConfigureServersDialog.h"

UiTamperNoServer::UiTamperNoServer(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperNoServerConfig{ false };

	noServerDescriptionLabel = new QLabel();
	noServerDescriptionLabel->setText(noServerDescriptionText);
	noServerDescriptionLabel->setFixedHeight(12);
	noServerDescriptionLabel->setAlignment(Qt::AlignHCenter);
	noServerDescriptionLabel->setFont(moduleDescriptionFont);
	noServerDescriptionLabel->setPalette(moduleTextPaletteInactive);

	noServerButton = new QPushButton();
	noServerButton->setCheckable(true);
	noServerButton->setStyleSheet(buttonStyleSheet);
	noServerButton->setFixedSize(100, 24);
	noServerButton->setText("Block Servers");
	noServerButton->setDisabled(true);

	blockedServersComboBox = new QComboBox();
	blockedServersComboBox->addItem(blockedServerFirstItemText + QString::number(blockedServersCount));
	blockedServersComboBox->setFixedSize(128, 24);
	blockedServersComboBox->setFont(moduleDescriptionFont);
	blockedServersComboBox->setPalette(moduleTextPaletteInactive);
	blockedServersComboBox->setEditable(true);
	blockedServersComboBox->lineEdit()->setReadOnly(true);
	blockedServersComboBox->lineEdit()->setFont(moduleDescriptionFont);
	blockedServersComboBox->view()->setFont(moduleDescriptionFont);
	blockedServersComboBox->lineEdit()->setPalette(lineEditPaletteInactive);
	blockedServersComboBox->setStyleSheet(comboBoxStyleSheet);
	blockedServersComboBox->lineEdit()->setDisabled(true);
	blockedServersComboBox->setDisabled(true);

	configServersButton = new QPushButton();
	configServersButton->setStyleSheet(buttonStyleSheet);
	configServersButton->setFixedSize(60, 24);
	configServersButton->setText("Configure");
	configServersButton->setDisabled(true);

	noServerLayout = new QGridLayout();
	noServerLayout->setAlignment(Qt::AlignHCenter);
	noServerLayout->setContentsMargins(10, 0, 10, 0);
	noServerLayout->addItem(new QSpacerItem(0, 6), 0, 0);
	noServerLayout->addWidget(noServerDescriptionLabel, 1, 0, 1, 3);
	noServerLayout->addItem(new QSpacerItem(0, 12), 2, 0);
	noServerLayout->addWidget(noServerButton, 3, 0, 1, 3, Qt::AlignHCenter);
	noServerLayout->addItem(new QSpacerItem(0, 10), 4, 0);
	noServerLayout->addWidget(blockedServersComboBox, 5, 0, 1, 2, Qt::AlignHCenter);
	noServerLayout->addWidget(configServersButton, 5, 2, Qt::AlignHCenter);



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
		blockedServersComboBox->lineEdit()->setPalette(this->lineEditPaletteActive);
		noServerButton->setEnabled(true);
		configServersButton->setEnabled(true);
		blockedServersComboBox->lineEdit()->setEnabled(true);
		blockedServersComboBox->setEnabled(true);
	}
	else
	{
		noServerDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		blockedServersComboBox->lineEdit()->setPalette(this->lineEditPaletteInactive);
		noServerButton->setDisabled(true);
		configServersButton->setDisabled(true);
		blockedServersComboBox->lineEdit()->setDisabled(true);
		blockedServersComboBox->setDisabled(true);
	}
}

void UiTamperNoServer::onConfigureServers()
{
	
	QList<QString> stringList;
	QPoint global = this->mapToGlobal(rect().center());
	ConfigureServersDialog* dialog = new ConfigureServersDialog(global, &stringList);
	dialog->exec();
	delete dialog;

	if (stringList.count() > 0)
	{
		//TODO: get this to the tamper module	

		blockedServersCount = stringList.count();
		blockedServersComboBox->clear();
		blockedServersComboBox->addItem(blockedServerFirstItemText + QString::number(blockedServersCount));

		QList<_Uint32t> ipList;

		for (int i = 0; i < stringList.count(); i++)
		{

			blockedServersComboBox->addItem(stringList[i]);

			_Uint32t ipAsInt = 0;
			InetPton(AF_INET, (const wchar_t*)stringList[i].split(" ").first().utf16(), &ipAsInt);

			ipList.append(ipAsInt);
		}


	}
}
