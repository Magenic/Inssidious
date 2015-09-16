#include "ConfigureServersDialog.h"

ConfigureServersDialog::ConfigureServersDialog(QPoint global, QList<QString> *ipList)
{
	saveList = ipList;
	this->global = global;

	this->setWindowTitle(dialogTitleText);
	this->setWindowIcon(QIcon(":/InssidiousUi/Inssidious.ico"));
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setStyleSheet(dialogStyleSheet);
	

	dialogPalette.setColor(QPalette::WindowText, QColor(230, 230, 230));
	dialogPalette.setColor(QPalette::ButtonText, QColor(0, 0, 0));

	dialogFont.setFamily("Segoe UI Semibold");
	dialogFont.setPixelSize(12);
	dialogFont.setWeight(QFont::DemiBold);
	dialogFont.setStyleStrategy(QFont::PreferAntialias);


	dialogTitle = new QLabel();
	dialogTitle->setText(dialogTitleText);
	dialogTitle->setPalette(dialogPalette);
	dialogTitle->setFont(QFont("Segoe UI Semibold", 15, QFont::DemiBold));
	dialogTitle->setAlignment(Qt::AlignHCenter);
	dialogTitle->setFixedHeight(30);

	listWidgetDescription = new QLabel("  Blocked:");
	listWidgetDescription->setFont(dialogFont);
	listWidgetDescription->setPalette(dialogPalette);
	listWidgetDescription->setFixedHeight(16);
	listWidget = new QListWidget();
	listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
	listWidget->setStyleSheet(listWidgetStyleSheet);

	dialogInstructions = new QLabel(dialogInstructionsText);
	dialogInstructions->setFixedHeight(16);
	dialogInstructions->setFont(dialogFont);
	dialogInstructions->setPalette(dialogPalette);

	input = new QLineEdit();
	input->setFont(dialogFont);
	input->setFixedWidth(140);

	buttonAdd = new QPushButton("Add");
	buttonAdd->setFont(dialogFont);
	buttonAdd->setFixedWidth(120); 
	buttonRemove = new QPushButton("Remove Selected");
	buttonRemove->setFont(dialogFont);
	buttonRemove->setFixedWidth(120); 
	buttonSave = new QPushButton("Save");
	buttonSave->setFont(dialogFont);
	buttonSave->setFixedWidth(120); 
	buttonCancel = new QPushButton("Cancel");
	buttonCancel->setFont(dialogFont);
	buttonCancel->setFixedWidth(120);


	connect(buttonAdd, &QPushButton::clicked, this, &ConfigureServersDialog::onAdd);
	connect(buttonRemove, &QPushButton::clicked, this, &ConfigureServersDialog::onRemove);
	connect(buttonSave, &QPushButton::clicked, this, &ConfigureServersDialog::onSave);
	connect(buttonCancel, &QPushButton::clicked, this, &ConfigureServersDialog::close);


	dialogGridLayout = new QGridLayout();
	dialogGridLayout->setAlignment(Qt::AlignHCenter);
	dialogGridLayout->addWidget(dialogTitle, 0, 0, 1, 2);
	dialogGridLayout->addWidget(dialogInstructions, 2, 0);
	dialogGridLayout->addWidget(listWidget, 2, 1, 6, 1);
	dialogGridLayout->addWidget(listWidgetDescription, 1, 1);
	dialogGridLayout->addWidget(input, 3, 0);
	dialogGridLayout->addWidget(buttonAdd, 4, 0, Qt::AlignHCenter);
	dialogGridLayout->addWidget(buttonRemove, 5, 0, Qt::AlignHCenter);
	dialogGridLayout->addItem(new QSpacerItem(20, 10), 6, 0);
	dialogGridLayout->addWidget(buttonSave, 7, 0, Qt::AlignHCenter);
	dialogGridLayout->addWidget(buttonCancel, 8, 0, Qt::AlignHCenter);


	setLayout(dialogGridLayout);

}

void ConfigureServersDialog::onAdd()
{
	input->setDisabled(true);
	buttonAdd->setDisabled(true);
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
			wchar_t strbuff[256];
			InetNtop(AF_INET, &addrAsUint32, strbuff, sizeof(strbuff));

			listWidget->addItem(QString::fromWCharArray(strbuff) + QString(" - ") + input->text());
		}
	}

	input->setEnabled(true);
	buttonAdd->setEnabled(true);
	buttonRemove->setEnabled(true);
	buttonSave->setEnabled(true);
}

void ConfigureServersDialog::onRemove()
{
	for (QListWidgetItem* item : listWidget->selectedItems())
	{
		delete item;
	}
}

void ConfigureServersDialog::onSave()
{
	saveList->clear();

	for (int i = 0; i < listWidget->count(); i++)
	{
		QListWidgetItem* item = listWidget->item(i);
		saveList->append(item->text());
		delete item;
	}

	emit close();
}

void ConfigureServersDialog::showEvent(QShowEvent* e)
{
	
	this->move(global.x() - this->width() / 2, global.y() - this->height() / 2);
	
}

