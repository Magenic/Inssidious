#include "ConfigureFirewallDialog.h"

ConfigureFirewallDialog::ConfigureFirewallDialog(QWidget* parent, QList<int> *portList)
	: QDialog(parent)
{
	saveList = portList;

	this->setWindowTitle("Configure Firewall");
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
	input->setPlaceholderText("22, 81, 589");

	presetOptions = new QComboBox();
	presetOptions->addItem("Email");
	presetOptions->addItem("HTTP");
	presetOptions->addItem("HTTPS");
	presetOptions->addItem("SSH");
	presetOptions->addItem("VPN");
	presetOptions->addItem("???");


	listWidgetDescription = new QLabel("Blocked Ports:");
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


	connect(buttonAddCustom, &QPushButton::clicked, this, &ConfigureFirewallDialog::onAddCustom);
	connect(buttonAddPreset, &QPushButton::clicked, this, &ConfigureFirewallDialog::onAddPreset);
	connect(buttonRemove, &QPushButton::clicked, this, &ConfigureFirewallDialog::onRemove);
	connect(buttonClear, &QPushButton::clicked, this, &ConfigureFirewallDialog::onClear);
	connect(buttonSave, &QPushButton::clicked, this, &ConfigureFirewallDialog::onSave);
	connect(buttonCancel, &QPushButton::clicked, this, &ConfigureFirewallDialog::close);


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

void ConfigureFirewallDialog::onAddCustom()
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

	if(this->input->text().contains(QRegExp("[^0-9,^,,^ ]")))
	{
		inputInstructions->setText("Please use a numeric, comma separated list:");
		inputInstructions->setPalette(dialogErrorPalette);
	}
	else
	{
		inputInstructions->setText(inputInstructionsText);
		inputInstructions->setPalette(dialogPalette);

		listWidget->addItems(input->text().remove(" ").split(","));


		/* Remove invalid port numbers and empty rows */

		for (int i = listWidget->count() - 1; i >= 0; i--)
		{
			if (listWidget->item(i)->text().isEmpty())
			{
				delete listWidget->item(i);
			}
			else if (listWidget->item(i)->text().toInt() > 65535 /* max port number */)
			{
				delete listWidget->item(i);
			}
		}

		/* Remove any duplicate port numbers */

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
	}

	input->setEnabled(true);
	buttonAddCustom->setEnabled(true);
	buttonAddPreset->setEnabled(true);
	buttonRemove->setEnabled(true);
	buttonSave->setEnabled(true);
}

void ConfigureFirewallDialog::onAddPreset()
{
	switch (presetOptions->currentIndex())
	{
	default:
		listWidget->addItem("80");
		listWidget->addItem("443");
		break;
	}




	/* Remove invalid port numbers and empty rows */

	for (int i = listWidget->count() - 1; i >= 0; i--)
	{
		if (listWidget->item(i)->text().isEmpty())
		{
			delete listWidget->item(i);
		}
		else if (listWidget->item(i)->text().toInt() > 65535 /* max port number */)
		{
			delete listWidget->item(i);
		}
	}

	/* Remove any duplicate port numbers */

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

void ConfigureFirewallDialog::onRemove()
{
	for (QListWidgetItem* item : listWidget->selectedItems())
	{
		delete item;
	}
}

void ConfigureFirewallDialog::onClear()
{
	for (int i = listWidget->count() - 1; i >= 0; i--)
	{
		QListWidgetItem* item = listWidget->item(i);
		delete item;
	}
}

void ConfigureFirewallDialog::onSave()
{
	saveList->clear();

	for (int i = listWidget->count() - 1; i >= 0; i--)
	{
		QListWidgetItem* item = listWidget->item(i);
		saveList->append(item->text().toInt());
		delete item;
	}

	emit accept();
}
