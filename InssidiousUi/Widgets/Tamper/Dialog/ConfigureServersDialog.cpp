#include "ConfigureServersDialog.h"

#include "winsock2.h"
#include "windns.h"
#pragma comment (lib, "Dnsapi.lib")

ConfigureServersDialog::ConfigureServersDialog(QWidget* parent, QList<QString> *serversList)
	: QDialog(parent)
{
	saveList = serversList;

	this->setWindowTitle("Configure Servers");
	this->setWindowIcon(QIcon(":/InssidiousUi/Inssidious.ico"));
	this->setStyleSheet(dialogStyleSheet);
	this->setFixedSize(390, 290);


	/* Center the dialog over the Inssidious window */

	QPoint dialogCenter = mapToGlobal(rect().center());
	QPoint parentWindowCenter = parent->window()->mapToGlobal(parent->window()->rect().center());
	move(parentWindowCenter - dialogCenter);


	dialogPalette.setColor(QPalette::WindowText, QColor(51, 51, 51));
	dialogErrorPalette.setColor(QPalette::WindowText, QColor(255, 150, 0, 255));
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
	presetOptions->addItem("(Coming Soon)");


	listWidgetDescription = new QLabel("Blocked Servers:");
	listWidgetDescription->setPalette(dialogPalette);
	listWidgetDescription->setFixedHeight(16);
	listWidgetDescription->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

	listWidget = new QListWidget();
	listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	listWidget->setStyleSheet(listWidgetStyleSheet);
	listWidget->setFixedHeight(82);

	for (auto i : *saveList)
	{
		listWidget->addItem(i);
	}


	buttonAddCustom = new QPushButton("Add");
	buttonAddPreset = new QPushButton("Add");
	buttonRemove = new QPushButton("Remove");
	buttonClear = new QPushButton("Clear");
	buttonSave = new QPushButton("Save");
	buttonCancel = new QPushButton("Cancel");


	connect(buttonAddCustom, &QPushButton::clicked, this, &ConfigureServersDialog::onAddCustom);
	connect(buttonAddPreset, &QPushButton::clicked, this, &ConfigureServersDialog::onAddPreset);
	connect(buttonRemove, &QPushButton::clicked, this, &ConfigureServersDialog::onRemove);
	connect(buttonClear, &QPushButton::clicked, this, &ConfigureServersDialog::onClear);
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
	dialogGridLayout->addWidget(listWidget, 5, 0, 4, 2, Qt::AlignTop | Qt::AlignHCenter);
	dialogGridLayout->addWidget(buttonRemove, 5, 2, 1, 1, Qt::AlignTop | Qt::AlignHCenter);
	dialogGridLayout->addWidget(buttonClear, 6, 2, 1, 1, Qt::AlignTop | Qt::AlignHCenter);
	dialogGridLayout->addItem(new QSpacerItem(10, 10), 8, 0);
	dialogGridLayout->addWidget(buttonSave, 9, 1, Qt::AlignRight);
	dialogGridLayout->addWidget(buttonCancel, 9, 2, Qt::AlignHCenter);


	setLayout(dialogGridLayout);
}

void ConfigureServersDialog::onAddCustom()
{
	if (this->input->text().isEmpty())
	{
		return;
	}

	input->setDisabled(true);
	buttonAddCustom->setDisabled(true);
	buttonAddPreset->setDisabled(true);
	buttonRemove->setDisabled(true);
	buttonSave->setDisabled(true);

	this->repaint();


	/* Confirm the input is valid */

	// Calling function DnsQuery to query Host or PTR records   

	PDNS_RECORD pDnsRecord;          //Pointer to DNS_RECORD structure.
	DNS_STATUS status = DnsQuery(PCTSTR(input->text().utf16()),     //Pointer to domain name. 
		DNS_TYPE_A,													//Type of the record to be queried.
		DNS_QUERY_BYPASS_CACHE | DNS_QUERY_NO_HOSTS_FILE,			// Bypasses the resolver cache on the lookup. 
		nullptr,													//Optional DNS server IP address.
		&pDnsRecord,												//Resource record that contains the response.
		nullptr);													//Reserved for future use.


	if (status)
	{
		inputInstructions->setText("Could not resolve: " + input->text());
		inputInstructions->setText(input->text() + " . Error: ");
		inputInstructions->setText(input->text() + QString::number(status));
		inputInstructions->setPalette(dialogErrorPalette);
	}
	else
	{
		inputInstructions->setText(inputInstructionsText);
		inputInstructions->setPalette(dialogPalette);

		PDNS_RECORD copyOfpDnsRecord = pDnsRecord;

		do
		{
			IN_ADDR ipaddr;
			ipaddr.S_un.S_addr = (copyOfpDnsRecord->Data.A.IpAddress);
			listWidget->addItem(QString::fromLocal8Bit(inet_ntoa(ipaddr)) + QString(" - ") + input->text());

			copyOfpDnsRecord = copyOfpDnsRecord->pNext;

		} while (copyOfpDnsRecord != nullptr);


		// Free memory allocated for DNS records. 
		DnsRecordListFree(pDnsRecord, DnsFreeRecordListDeep);

	}
	//QHostInfo host = QHostInfo::fromName(this->input->text());
	//if (host.error())
	//{
	//	inputInstructions->setText("Could not resolve: " + input->text());
	//	inputInstructions->setPalette(dialogErrorPalette);
	//}
	//else
	//{
	//	inputInstructions->setText(inputInstructionsText);
	//	inputInstructions->setPalette(dialogPalette);

	//	QList<QHostAddress> addressList = host.addresses();

	//	for (QHostAddress addr : addressList)
	//	{
	//		QHostAddress dumb = QHostAddress(addr.toIPv4Address());
	//		//_Uint32t addrAsUint32 = addr.toIPv4Address();
	//		//wchar_t strbuff[512];
	//		//InetNtop(AF_INET, &addrAsUint32, strbuff, sizeof(strbuff));

	//		//listWidget->addItem(QString::fromWCharArray(strbuff) + QString(" - ") + input->text());
	//		listWidget->addItem(QString::fromWCharArray(dumb.toString().utf16()) + QString(" - ") + input->text());
	//	}
	//}


	/* Remove any duplicate entries */

	for (int i = 0; i < listWidget->count(); i++)
	{
		for (int j = listWidget->count() - 1; j > i; j--)
		{
			if (listWidget->item(j)->text() == listWidget->item(i)->text())
			{
				delete listWidget->item(j);
			}
		}
	}

	input->clear();
	

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
	//case 0: 
	//	for (auto i : list)
	//	{
	//		listWidget->addItem(i);
	//	}
	//	break;
	default:
		break;
	}


	/* Remove any duplicate entries */

	for (int i = 0; i < listWidget->count(); i++)
	{
		for (int j = listWidget->count() - 1; j > i; j--)
		{
			if (listWidget->item(j)->text() == listWidget->item(i)->text())
			{
				delete listWidget->item(j);
			}
		}
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
	for (int i = listWidget->count() - 1; i >= 0; i--)
	{
		QListWidgetItem* item = listWidget->item(i);
		delete item;
	}
}

void ConfigureServersDialog::onSave()
{
	saveList->clear();

	if (listWidget->count() == 0)
	{
		/* No custom ports */
		emit reject();
		return;
	}


	/* Save the servers to the list */

	for (int i = listWidget->count() - 1; i >= 0; i--)
	{
		QListWidgetItem* item = listWidget->item(i);
		saveList->append(item->text());
		delete item;
	}

	emit accept();
}
