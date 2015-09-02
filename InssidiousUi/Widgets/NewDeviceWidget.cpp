#include "NewDeviceWidget.h"

NewDeviceWidget::NewDeviceWidget(QWidget *parent, QString MACAddress)
	: QWidget(parent)
{

	MAC = MACAddress;


	backgroundPalette.setBrush(QPalette::Background, QBrush(backgroundImage));

	this->setAutoFillBackground(true);
	this->setPalette(backgroundPalette);
	this->setGeometry(10 /* in */, 108 /* down */, 780 /* width */, 480 /* height */);

	this->ndlayout = new QVBoxLayout();
	this->ndlayout->setAlignment(Qt::AlignHCenter);
	this->ndlayout->setSpacing(0);
	this->setLayout(ndlayout);


	//Set the default description Window text to a light grey
	descriptionTextPalette.setColor(QPalette::WindowText, QColor(230, 230, 230));	

	//Set the error description Window text to a bright red
	errorTextPalette.setColor(QPalette::WindowText, QColor(255, 150, 0, 255));								



	//Set the device name text label and initialize the line edit
	deviceNameTextLabel = new QLabel("Specify the name of the device:");
	deviceNameTextLabel->setPalette(descriptionTextPalette);
	deviceNameTextLabel->setAlignment(Qt::AlignHCenter);
	deviceNameTextLabel->setFixedHeight(26);
	deviceNameLineEdit = new QLineEdit();
	deviceNameLineEdit->setMaximumSize(160, 20);
	deviceNameLineEdit->setAlignment(Qt::AlignHCenter);

	//Add them to the layout
	ndlayout->setContentsMargins(40, 60, 40, 0);
	ndlayout->addWidget(deviceNameTextLabel, Qt::AlignHCenter);
	ndlayout->addWidget(deviceNameLineEdit, Qt::AlignHCenter);
	ndlayout->setAlignment(deviceNameLineEdit, Qt::AlignHCenter);
	ndlayout->addSpacing(20);

	//Initialize the device type icons image list
	deviceIconImageListTextLabel = new QLabel("Select a device icon: ");
	deviceIconImageListTextLabel->setPalette(descriptionTextPalette);
	deviceIconImageListTextLabel->setAlignment(Qt::AlignHCenter);
	deviceIconImageListTextLabel->setFixedHeight(26);
	deviceIconImageList = new QListView();
	deviceIconImageList->setFixedSize(460, 230);
	deviceIconImageList->setContentsMargins(20, 20, 20, 20);
	deviceIconImageList->setAutoFillBackground(false);
	deviceIconImageList->setStyleSheet("background-color: transparent;");

	deviceIconImageList->setViewMode(QListView::IconMode);

	iStandardModel = new QStandardItemModel(this);
	QStandardItem* item1 = new QStandardItem(QIcon(":/Device/iPhoneInactive.png"), "iPhone");
	QStandardItem* item2 = new QStandardItem(QIcon(":/Device/AndroidInactive.png"), "Android");
	QStandardItem* item3 = new QStandardItem(QIcon(":/Device/WindowsPhoneInactive.png"), "Windows Phone");
	QStandardItem* item4 = new QStandardItem(QIcon(":/Device/iPadInactive.png"), "iPad");
	QStandardItem* item5 = new QStandardItem(QIcon(":/Device/AndroidTabletInactive.png"), "Android Tablet");
	QStandardItem* item6 = new QStandardItem(QIcon(":/Device/WindowsTabletInactive.png"), "Windows Tablet");
	QStandardItem* item7 = new QStandardItem(QIcon(":/Device/MacBookInactive.png"), "MacBook");
	QStandardItem* item8 = new QStandardItem(QIcon(":/Device/ChromebookInactive.png"), "Chromebook");
	QStandardItem* item9 = new QStandardItem(QIcon(":/Device/WindowsLaptopInactive.png"), "Windows Laptop");

	item1->setForeground(QColor(230, 230, 230));
	item2->setForeground(QColor(230, 230, 230));
	item3->setForeground(QColor(230, 230, 230));
	item4->setForeground(QColor(230, 230, 230));
	item5->setForeground(QColor(230, 230, 230));
	item6->setForeground(QColor(230, 230, 230));
	item7->setForeground(QColor(230, 230, 230));
	item8->setForeground(QColor(230, 230, 230));
	item9->setForeground(QColor(230, 230, 230));

	iStandardModel->appendRow(item1);
	iStandardModel->appendRow(item2);
	iStandardModel->appendRow(item3);
	iStandardModel->appendRow(item4);
	iStandardModel->appendRow(item5);
	iStandardModel->appendRow(item6);
	iStandardModel->appendRow(item7);
	iStandardModel->appendRow(item8);
	iStandardModel->appendRow(item9);

	deviceIconImageList->setIconSize(QSize(48, 48));
	deviceIconImageList->setGridSize(QSize(140, 70));
	deviceIconImageList->setFrameStyle(0);
	deviceIconImageList->setUniformItemSizes(true);
	deviceIconImageList->setPalette(descriptionTextPalette);
	deviceIconImageList->setSelectionMode(QAbstractItemView::ExtendedSelection);
	deviceIconImageList->setDragDropMode(QAbstractItemView::DropOnly);
	deviceIconImageList->setModel(iStandardModel);


	//Add them to the layout
	ndlayout->addWidget(deviceIconImageListTextLabel, Qt::AlignHCenter);
	ndlayout->addWidget(deviceIconImageList, Qt::AlignHCenter);
	ndlayout->setAlignment(deviceIconImageList, Qt::AlignHCenter);
	ndlayout->addSpacing(10);

	//Draw the Set New Device Info button
	setNewDeviceInfoButton = new QPushButton();
	setNewDeviceInfoButton->setMinimumSize(QSize(104, 30));
	setNewDeviceInfoButton->setStyleSheet("QPushButton{ border: none; background-image: url(\":/Device/SetButtonActive.png\"); }QPushButton:!enabled{background-image: url(\":/Device/SetButtonInactive.png\");}QPushButton:hover{ background-image: url(\":/Device/SetButtonHover.png\");}QPushButton:pressed{ background-image: url(\":/Device/SetButtonPressed.png\");}QPushButton:focus { outline: none;}");
	ndlayout->addWidget(setNewDeviceInfoButton, 0, Qt::AlignCenter);

	//Pad out the bottom of the layout
	ndlayout->addStretch();

	//Connect the start button signal & slot
	connect(setNewDeviceInfoButton, &QPushButton::clicked, this, &NewDeviceWidget::onSetButtonClicked);


}

NewDeviceWidget::~NewDeviceWidget()
{

}

void NewDeviceWidget::onSetButtonClicked()
{
	QString deviceType = "UnknownDevice"; /* default device type if none was selected */

	for (const QModelIndex &index : deviceIconImageList->selectionModel()->selectedIndexes())
	{
		deviceType = iStandardModel->itemFromIndex(index)->text();
	}


	//Check whether the Device Name is of appropriate length
	if (deviceNameLineEdit->text().count() < 1 || deviceNameLineEdit->text().count() > 12) //1 - 12 is the valid length range
	{
		deviceNameTextLabel->setText("The device name must be between 1-12 characters:");
		deviceNameTextLabel->setPalette(errorTextPalette);
	}
	else
	{
		//Set the device name and type values
		emit setDeviceInfo(MAC, deviceNameLineEdit->text(), deviceType.remove(" ")); /* remove spaces to line up device types with icon names */

	}

}