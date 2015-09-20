#include "ConfigureServersDialog.h"

#include <WS2tcpip.h>
#include <QtNetwork/QHostInfo>
#pragma comment(lib, "Qt5Network.lib")	


ConfigureServersDialog::ConfigureServersDialog(QWidget* parent, QList<unsigned int> *ipList)
	: QDialog(parent)
{
	saveList = ipList;

	this->setWindowTitle("Configure Servers");
	this->setWindowIcon(QIcon(":/InssidiousUi/Inssidious.ico"));
	this->setStyleSheet(dialogStyleSheet);
	this->setFixedSize(400, 300);


	/* Center the dialog over the Inssidious window */

	QPoint dialogCenter = mapToGlobal(rect().center());
	QPoint parentWindowCenter = parent->window()->mapToGlobal(parent->window()->rect().center());
	move(parentWindowCenter - dialogCenter);


	dialogPalette.setColor(QPalette::WindowText, QColor(51, 51, 51));
	dialogPalette.setColor(QPalette::ButtonText, QColor(51, 51, 51));

	dialogFont.setFamily("Segoe UI Semibold");
	dialogFont.setPixelSize(12);
	dialogFont.setWeight(QFont::DemiBold);
	dialogFont.setStyleStrategy(QFont::PreferAntialias);


	dialogTitle = new QLabel();
	dialogTitle->setText(dialogTitleText);
	dialogTitle->setPalette(dialogPalette);
	dialogTitle->setWordWrap(true);
	dialogTitle->setAlignment(Qt::AlignTop);
	dialogTitle->setFixedHeight(42);

	inputInstructions = new QLabel(inputInstructionsText);
	inputInstructions->setFixedHeight(16);
	inputInstructions->setPalette(dialogPalette);

	input = new QLineEdit();
	input->setPlaceholderText("server.example.com");

	presetOptions = new QComboBox();
	presetOptions->addItem("Apple iCloud");
	presetOptions->addItem("Google Play");
	presetOptions->addItem("???");

	listWidgetDescription = new QLabel("Blocked Servers:");
	listWidgetDescription->setPalette(dialogPalette);
	listWidgetDescription->setFixedHeight(16);
	listWidgetDescription->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

	listWidget = new QListWidget();
	listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	listWidget->setStyleSheet(listWidgetStyleSheet);
	listWidget->setFixedHeight(82);



	buttonAddCustom = new QPushButton("Add");
	buttonAddPreset = new QPushButton("Add");
	buttonRemove = new QPushButton("Remove");
	buttonClear = new QPushButton("Clear");
	buttonSave = new QPushButton("Save");
	buttonCancel = new QPushButton("Cancel");


	connect(buttonAddCustom, &QPushButton::clicked, this, &ConfigureServersDialog::onAddCustom);
	connect(buttonAddPreset, &QPushButton::clicked, this, &ConfigureServersDialog::onAddPreset);
	connect(buttonRemove, &QPushButton::clicked, this, &ConfigureServersDialog::onRemove);
	connect(buttonSave, &QPushButton::clicked, this, &ConfigureServersDialog::onSave);
	connect(buttonCancel, &QPushButton::clicked, this, &ConfigureServersDialog::close);


	dialogGridLayout = new QGridLayout();
	dialogGridLayout->setAlignment(Qt::AlignHCenter);

	dialogGridLayout->addWidget(dialogTitle, 0, 0, 1, 3);
	dialogGridLayout->addWidget(inputInstructions, 1, 0, 1, 2);
	dialogGridLayout->addWidget(input, 2, 0, 1, 2);
	dialogGridLayout->addWidget(buttonAddCustom, 2, 2, 1, 1, Qt::AlignHCenter);
	dialogGridLayout->addWidget(presetOptions, 3, 0, 1, 2);
	dialogGridLayout->addWidget(buttonAddPreset, 3, 2, 1, 1, Qt::AlignHCenter);
	dialogGridLayout->addWidget(listWidgetDescription, 4, 0, 1, 3);
	dialogGridLayout->addWidget(listWidget, 5, 0, 4, 2);
	dialogGridLayout->addWidget(buttonRemove, 5, 2, 1, 1, Qt::AlignTop | Qt::AlignHCenter);
	dialogGridLayout->addWidget(buttonClear, 6, 2, 1, 1, Qt::AlignTop | Qt::AlignHCenter);
	dialogGridLayout->addItem(new QSpacerItem(10, 10), 8, 0);
	dialogGridLayout->addWidget(buttonSave, 9, 1, Qt::AlignRight);
	dialogGridLayout->addWidget(buttonCancel, 9, 2, Qt::AlignHCenter);


	setLayout(dialogGridLayout);

}

void ConfigureServersDialog::onAddCustom()
{
	input->setDisabled(true);
	buttonAddCustom->setDisabled(true);
	buttonAddPreset->setDisabled(true);
	buttonRemove->setDisabled(true);
	buttonSave->setDisabled(true);

	this->repaint();


	/* Resolve name to an IP Address */

	QHostInfo host = QHostInfo::fromName(this->input->text());

	if (host.error())
	{
		input->setText("Could not resolve: " + input->text());
	}
	else
	{
		QList<QHostAddress> addressList = host.addresses();

		for (QHostAddress addr : addressList)
		{
			_Uint32t addrAsUint32 = addr.toIPv4Address();
			wchar_t strbuff[512];
			InetNtop(AF_INET, &addrAsUint32, strbuff, sizeof(strbuff));

			listWidget->addItem(QString::fromWCharArray(strbuff) + QString(" - ") + input->text());
		}
	}

	input->setEnabled(true);
	buttonAddCustom->setEnabled(true);
	buttonAddPreset->setEnabled(true);
	buttonRemove->setEnabled(true);
	buttonSave->setEnabled(true);
}

void ConfigureServersDialog::onAddPreset()
{
	switch (presetOptions->currentIndex())
	{
	default:
		listWidget->addItem("combo");
		break;
	}
}

void ConfigureServersDialog::onRemove()
{
	for (QListWidgetItem* item : listWidget->selectedItems())
	{
		delete item;
	}
}

void ConfigureServersDialog::onClear()
{
	for (int i = 0; i < listWidget->count(); i++)
	{
		QListWidgetItem* item = listWidget->item(i);
		delete item;
	}
}

void ConfigureServersDialog::onSave()
{
	saveList->clear();

	for (int i = 0; i < listWidget->count(); i++)
	{
		QListWidgetItem* item = listWidget->item(i);
		saveList->append(inet_addr(item->text().toLocal8Bit()));
		delete item;
	}

	emit close();
}
