#include "ConfigureFirewallDialog.h"

ConfigureFirewallDialog::ConfigureFirewallDialog(QWidget* parent, QList<QString> *ipList)
	: QDialog(parent)
{
	saveList = ipList;

	this->setWindowTitle("Configure Servers");
	this->setWindowIcon(QIcon(":/InssidiousUi/Inssidious.ico"));
	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setStyleSheet(dialogStyleSheet);
	this->setFixedSize(360, 260);

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
	//dialogTitle->setFont(dialogFont);
	dialogTitle->setAlignment(Qt::AlignTop);
	dialogTitle->setFixedHeight(46);

	listWidgetDescription = new QLabel("Blocked Servers:");
	//listWidgetDescription->setFont(dialogFont);
	listWidgetDescription->setPalette(dialogPalette);
	listWidgetDescription->setFixedHeight(20);
	listWidgetDescription->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

	listWidget = new QListWidget();
	listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	listWidget->setStyleSheet(listWidgetStyleSheet);
	listWidget->setFixedHeight(82);

	dialogInstructions = new QLabel(dialogInstructionsText);
	dialogInstructions->setFixedHeight(16);
	//dialogInstructions->setFont(dialogFont);
	dialogInstructions->setPalette(dialogPalette);

	input = new QLineEdit();
	input->setPlaceholderText("server.example.com");
	//input->setFont(dialogFont);

	buttonAdd = new QPushButton("Add");
	buttonRemove = new QPushButton("Remove");
	buttonClear = new QPushButton("Clear");
	buttonSave = new QPushButton("Save");
	buttonCancel = new QPushButton("Cancel");


	connect(buttonAdd, &QPushButton::clicked, this, &ConfigureFirewallDialog::onAdd);
	connect(buttonRemove, &QPushButton::clicked, this, &ConfigureFirewallDialog::onRemove);
	connect(buttonSave, &QPushButton::clicked, this, &ConfigureFirewallDialog::onSave);
	connect(buttonCancel, &QPushButton::clicked, this, &ConfigureFirewallDialog::close);


	dialogGridLayout = new QGridLayout();
	dialogGridLayout->setAlignment(Qt::AlignHCenter);

	dialogGridLayout->addWidget(dialogTitle, 0, 0, 1, 3);
	dialogGridLayout->addWidget(dialogInstructions, 1, 0, 1, 2);
	dialogGridLayout->addWidget(input, 2, 0, 1, 2);
	dialogGridLayout->addWidget(buttonAdd, 2, 2, 1, 1, Qt::AlignHCenter);
	dialogGridLayout->addWidget(listWidgetDescription, 3, 0, 1, 3);
	dialogGridLayout->addWidget(listWidget, 4, 0, 4, 2);
	dialogGridLayout->addWidget(buttonRemove, 4, 2, 1, 1, Qt::AlignTop | Qt::AlignHCenter);
	dialogGridLayout->addWidget(buttonClear, 5, 2, 1, 1, Qt::AlignTop | Qt::AlignHCenter);
	dialogGridLayout->addItem(new QSpacerItem(10, 10), 8, 0);
	dialogGridLayout->addWidget(buttonSave, 9, 1, Qt::AlignRight);
	dialogGridLayout->addWidget(buttonCancel, 9, 2, Qt::AlignHCenter);


	setLayout(dialogGridLayout);

}

void ConfigureFirewallDialog::onAdd()
{
	input->setDisabled(true);
	buttonAdd->setDisabled(true);
	buttonRemove->setDisabled(true);
	buttonSave->setDisabled(true);

	this->repaint();


	///* Resolve name to an IP Address */

	//QHostInfo host = QHostInfo::fromName(this->input->text());

	//if (host.error())
	//{
	//	input->setText("Could not resolve: " + input->text());
	//}
	//else
	//{
	//	QList<QHostAddress> addressList = host.addresses();

	//	for (QHostAddress addr : addressList)
	//	{
	//		_Uint32t addrAsUint32 = addr.toIPv4Address();
	//		wchar_t strbuff[512];
	//		InetNtop(AF_INET, &addrAsUint32, strbuff, sizeof(strbuff));

	//		listWidget->addItem(QString::fromWCharArray(strbuff) + QString(" - ") + input->text());
	//	}
	//}

	input->setEnabled(true);
	buttonAdd->setEnabled(true);
	buttonRemove->setEnabled(true);
	buttonSave->setEnabled(true);
}

void ConfigureFirewallDialog::onRemove()
{
	for (QListWidgetItem* item : listWidget->selectedItems())
	{
		delete item;
	}
}

void ConfigureFirewallDialog::onSave()
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

void ConfigureFirewallDialog::showEvent(QShowEvent* e)
{

	//this->move(global.x() - this->width() / 2, global.y() - this->height() / 2);

}

