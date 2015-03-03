#include "startupwidget.h"

StartupWidget::StartupWidget(QWidget *parent)
	: QWidget(parent)
{
	//Initialize and set the layout for StartupWidget
	startupWidgetLayout = new QVBoxLayout();
	startupWidgetLayout->setSpacing(0); 
	startupWidgetLayout->setContentsMargins(225, 120, 225, 0); /* pushes all content into the middle of the window */
	this->setLayout(startupWidgetLayout);

	//Set the size policy and size of StartupWidget
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setMinimumSize(762, 644);

	//Set the background color of the StartupWidget to a grey black
	QPalette startupWidgetPalette(palette());
	startupWidgetPalette.setColor(QPalette::Background, QColor(42, 42, 42, 255));
	this->setAutoFillBackground(true);
	this->setPalette(startupWidgetPalette);

	//Draw the Inssidious logo and add it to the layout
	inssidiousLogo = new QLabel();
	inssidiousLogo->setPixmap(QPixmap(":/StartupWidget/AppLogo.png"));
	startupWidgetLayout->addWidget(inssidiousLogo, 0, Qt::AlignCenter);

	//Draw the Inssidious tag line and add it to the layout
	inssidiousTagLine = new QLabel();
	inssidiousTagLine->setPixmap(QPixmap(":/StartupWidget/AppTagLine.png"));
	startupWidgetLayout->addWidget(inssidiousTagLine, 0, Qt::AlignCenter);

	//Set the description text palette to a light grey 
	descriptionTextPalette.setColor(QPalette::WindowText, QColor("lightGray"));

	//Set the error text palette to red 
	errorTextPalette.setColor(QPalette::WindowText, QColor(255, 150, 0, 255));

	/* No further drawing performed until Core emits Started or StartFailed */
	
}

void StartupWidget::onCoreThreadReady()
{
	//Draw the Internet Connection description field
	internetConnectionText = new QLabel();
	internetConnectionText->setText("Select an internet connection:");
	internetConnectionText->setPalette(descriptionTextPalette);
	internetConnectionText->setContentsMargins(0, 20, 0, 2); /* padding to push away from logo and tag line */
	startupWidgetLayout->addWidget(internetConnectionText, 0, Qt::AlignTop);
	
	//Draw the Internet Connection combo box
	internetConnectionComboBox = new QComboBox();
	startupWidgetLayout->addWidget(internetConnectionComboBox, 0, Qt::AlignTop);
	
	//Draw the Wireless Adapter description field
	wirelessAdapterText = new QLabel();
	wirelessAdapterText->setText("Select a wireless adapter:");
	wirelessAdapterText->setPalette(descriptionTextPalette);
	wirelessAdapterText->setContentsMargins(0, 10, 0, 2); /* padding from combo box above */
	startupWidgetLayout->addWidget(wirelessAdapterText, 0, Qt::AlignTop);
	
	//Draw the Wireless Adapter combo box
	wirelessAdapterComboBox = new QComboBox();
	startupWidgetLayout->addWidget(wirelessAdapterComboBox, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Name description field
	wirelessNetworkNameText = new QLabel();
	wirelessNetworkNameText->setText("Specify the name of the Inssidious wireless network:");
	wirelessNetworkNameText->setPalette(descriptionTextPalette);
	wirelessNetworkNameText->setContentsMargins(0, 10, 0, 2); /* padding from combo box above */
	startupWidgetLayout->addWidget(wirelessNetworkNameText, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Name line edit field
	wirelessNetworkNameLineEdit = new QLineEdit();
	wirelessNetworkNameLineEdit->setText("Inssidious - Ian");
	startupWidgetLayout->addWidget(wirelessNetworkNameLineEdit, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Password description field
	wirelessNetworkPasswordText = new QLabel();
	wirelessNetworkPasswordText->setText("Specify the password for the Inssidious wireless network:");
	wirelessNetworkPasswordText->setPalette(descriptionTextPalette);
	wirelessNetworkPasswordText->setContentsMargins(0, 10, 0, 2); /* padding from line edit above */
	startupWidgetLayout->addWidget(wirelessNetworkPasswordText, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Password line edit field
	wirelessNetworkPasswordLineEdit = new QLineEdit();
	wirelessNetworkPasswordLineEdit->setText("inssidious");
	startupWidgetLayout->addWidget(wirelessNetworkPasswordLineEdit, 0, Qt::AlignTop);
	
	//Draw the Start button
	inssidiousStartButton = new QPushButton();
	inssidiousStartButton->setMinimumSize(QSize(104, 30));
	inssidiousStartButton->setStyleSheet("QPushButton{ border: none; background-image: url(\":/StartupWidget/StartButtonActive.png\"); }QPushButton:!enabled{background-image: url(\":/StartupWidget/StartButtonInactive.png\");}QPushButton:hover{ background-image: url(\":/StartupWidget/StartButtonHover.png\");}QPushButton:pressed{ background-image: url(\":/StartupWidget/StartButtonPressed.png\");}QPushButton:focus { outline: none;}");
	startupWidgetLayout->addSpacing(15); /* padding from line edit above */
	startupWidgetLayout->addWidget(inssidiousStartButton, 0, Qt::AlignCenter);
	
	//Pad the remaining layout space at the bottom to push content up
	startupWidgetLayout->addStretch();
	
	//Connect the start button signal & slot
	connect(inssidiousStartButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
	
	//Get the names of all network adapters from Core
	lNetworkAdapters = Core::getNetworkAdapters();
	
	//Check if the first entry is an error, condition if so
	if (lNetworkAdapters.first().AdapterPhysType == 2 /* error message */ )
	{
		//Display the error text in red in place of the description
		internetConnectionText->setText(lNetworkAdapters.first().AdapterDescription);
		internetConnectionText->setPalette(errorTextPalette);

		//Clear the wireless description text
		wirelessAdapterText->setText("");

		//Disable the combo boxes
		internetConnectionComboBox->setDisabled(true);
		wirelessAdapterComboBox->setDisabled(true);

		//Disable the start button
		inssidiousStartButton->setDisabled(true);

		//No further work can be done, return.
		return;
	}
	else //We have a valid list of network adapters
	{
		for (Core::NetworkAdapter networkAdapter : lNetworkAdapters)
		{
			//Add each of them to the Internet Connection combo box
			internetConnectionComboBox->addItem(networkAdapter.AdapterDescription);

			//Add wireless ones to the wireless adapter combo box
			if (networkAdapter.AdapterPhysType == 1 /* wireless adapter */)
			{
				wirelessAdapterComboBox->addItem(networkAdapter.AdapterDescription);
			}
		}
	}
}

void StartupWidget::onStartButtonClicked()
{
	//Check fields for validity

	//Signal to core to start Inssidious
	emit coreStartInssidious(/* put info here */);
}
