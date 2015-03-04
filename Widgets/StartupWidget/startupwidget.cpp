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
	internetConnectionTextLabel = new QLabel();
	internetConnectionTextLabel->setText(internetConnectionText);
	internetConnectionTextLabel->setPalette(descriptionTextPalette);
	internetConnectionTextLabel->setContentsMargins(0, 20, 0, 2); /* padding to push away from logo and tag line */
	startupWidgetLayout->addWidget(internetConnectionTextLabel, 0, Qt::AlignTop);
	
	//Draw the Internet Connection combo box
	internetConnectionComboBox = new QComboBox();
	startupWidgetLayout->addWidget(internetConnectionComboBox, 0, Qt::AlignTop);
	
	//Draw the Wireless Adapter description field
	wirelessAdapterTextLabel = new QLabel();
	wirelessAdapterTextLabel->setText(wirelessAdapterText);
	wirelessAdapterTextLabel->setPalette(descriptionTextPalette);
	wirelessAdapterTextLabel->setContentsMargins(0, 10, 0, 2); /* padding from combo box above */
	startupWidgetLayout->addWidget(wirelessAdapterTextLabel, 0, Qt::AlignTop);
	
	//Draw the Wireless Adapter combo box
	wirelessAdapterComboBox = new QComboBox();
	startupWidgetLayout->addWidget(wirelessAdapterComboBox, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Name description field
	wirelessNetworkNameTextLabel = new QLabel();
	wirelessNetworkNameTextLabel->setText(wirelessNetworkNameText);
	wirelessNetworkNameTextLabel->setPalette(descriptionTextPalette);
	wirelessNetworkNameTextLabel->setContentsMargins(0, 10, 0, 2); /* padding from combo box above */
	startupWidgetLayout->addWidget(wirelessNetworkNameTextLabel, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Name line edit field
	wirelessNetworkNameLineEdit = new QLineEdit();
	wirelessNetworkNameLineEdit->setText("Inssidious - Ian");
	startupWidgetLayout->addWidget(wirelessNetworkNameLineEdit, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Password description field
	wirelessNetworkPasswordTextLabel = new QLabel();
	wirelessNetworkPasswordTextLabel->setText(wirelessNetworkPasswordText);
	wirelessNetworkPasswordTextLabel->setPalette(descriptionTextPalette);
	wirelessNetworkPasswordTextLabel->setContentsMargins(0, 10, 0, 2); /* padding from line edit above */
	startupWidgetLayout->addWidget(wirelessNetworkPasswordTextLabel, 0, Qt::AlignTop);
	
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
	if (lNetworkAdapters.first().AdapterPhysType == Core::ERROR_QUERYING_ADAPTERS)
	{
		//Display the error text in red in place of the description
		internetConnectionTextLabel->setText(lNetworkAdapters.first().AdapterDescription);
		internetConnectionTextLabel->setPalette(errorTextPalette);

		//Clear the wireless description text
		wirelessAdapterTextLabel->setText("");

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
			if (networkAdapter.AdapterPhysType == Core::WIRELESS || networkAdapter.AdapterPhysType == Core::WIRELESS_HOSTED_NETWORK_CAPABLE)
			{
				wirelessAdapterComboBox->addItem(networkAdapter.AdapterDescription);
			}
		}
	}
}

void StartupWidget::onStartButtonClicked()
{
	//Bool to abort signaling core if any data is invalid
	bool dataIsValid = true;

	//Reset description texts & palettes
	internetConnectionTextLabel->setText(internetConnectionText);
	internetConnectionTextLabel->setPalette(descriptionTextPalette);
	wirelessAdapterTextLabel->setText(wirelessAdapterText);
	wirelessAdapterTextLabel->setPalette(descriptionTextPalette);
	wirelessNetworkNameTextLabel->setText(wirelessNetworkNameText);
	wirelessNetworkNameTextLabel->setPalette(descriptionTextPalette);
	wirelessNetworkPasswordTextLabel->setText(wirelessNetworkPasswordText);
	wirelessNetworkPasswordTextLabel->setPalette(descriptionTextPalette);

	//Check whether both Internet Connection and Wireless Adapter combo boxes are set to the same adapter
	if (internetConnectionComboBox->currentText() == wirelessAdapterComboBox->currentText())
	{
		internetConnectionTextLabel->setText("The selected adapter doesn't support Wireless Hosted Networks.\nPlease select another wireless adapter:");
		internetConnectionTextLabel->setText("The selected Internet Connection and Wireless Adapter cannot\nbe the same. Please select another internet connection:");
		internetConnectionTextLabel->setPalette(errorTextPalette);
		dataIsValid = false;
	}

	//Check whether the selected wireless adapter supports Hosted Network functionality
	for (Core::NetworkAdapter networkAdapter : lNetworkAdapters)
	{
		if (wirelessAdapterComboBox->currentText() == networkAdapter.AdapterDescription)
		{
			if (networkAdapter.AdapterPhysType != Core::WIRELESS_HOSTED_NETWORK_CAPABLE)
			{
				wirelessAdapterTextLabel->setText("The selected adapter doesn't support Wireless Hosted Networks.\nPlease select another wireless adapter:");
				wirelessAdapterTextLabel->setPalette(errorTextPalette);
				dataIsValid = false;
			}
		}
	}
	
	//Check whether the Inssidious Wireless Network Name is of appropriate length
	if (wirelessNetworkNameLineEdit->text().count() < 1 || wirelessNetworkNameLineEdit->text().count() > 32) //1 - 32 is the valid SSID key length range
	{
		wirelessNetworkNameTextLabel->setText("The wireless network name must be between 1-32 characters:");
		wirelessNetworkNameTextLabel->setPalette(errorTextPalette);
		dataIsValid = false;
	}

	//Check whether the Inssidious Wireless Network Name uses only simple ASCII characters 
	for (QChar c : wirelessNetworkNameLineEdit->text())
	{
		if (c.unicode() < 20 || c.unicode() > 126) //20 - 126 are simple ascii characters
		{
			wirelessNetworkNameTextLabel->setText("Please only use ASCII characters:");
			wirelessNetworkNameTextLabel->setPalette(errorTextPalette);
			dataIsValid = false;
		}
	}
	
	//Check whether the Inssidious Wireless Network Password is of appropriate length
	if (wirelessNetworkPasswordLineEdit->text().count() < 8 || wirelessNetworkPasswordLineEdit->text().count() > 63) //8 - 63 is the valid SSID key length range
	{
		wirelessNetworkPasswordTextLabel->setText("The wireless password must be between 8-63 characters:");
		wirelessNetworkPasswordTextLabel->setPalette(errorTextPalette);
		dataIsValid = false;
	}

	//Check whether the Inssidious Wireless Network Password uses only simple ASCII characters 
	for (QChar c : wirelessNetworkPasswordLineEdit->text())
	{
		if (c.unicode() < 20 || c.unicode() > 126) //20 - 126 are simple ascii characters
		{
			wirelessNetworkPasswordTextLabel->setText("Please only use ASCII characters:");
			wirelessNetworkPasswordTextLabel->setPalette(errorTextPalette);
			dataIsValid = false;
		}
	}

	//Signal to core to start Inssidious if data was valid
	if (dataIsValid)
	{
		emit coreStartInssidious(/* put info here */);
	}
}
