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

void StartupWidget::onCoreReadyToStart()
{
	
	//Draw the Wireless Network Name description field
	wirelessNetworkNameTextLabel = new QLabel();
	wirelessNetworkNameTextLabel->setText(wirelessNetworkNameText);
	wirelessNetworkNameTextLabel->setPalette(descriptionTextPalette);
	wirelessNetworkNameTextLabel->setContentsMargins(0, 25, 0, 4); /* padding from combo box above */
	startupWidgetLayout->addWidget(wirelessNetworkNameTextLabel, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Name line edit field
	wirelessNetworkNameLineEdit = new QLineEdit();
	wirelessNetworkNameLineEdit->setText("Inssidious - Ian");
	startupWidgetLayout->addWidget(wirelessNetworkNameLineEdit, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Password description field
	wirelessNetworkPasswordTextLabel = new QLabel();
	wirelessNetworkPasswordTextLabel->setText(wirelessNetworkPasswordText);
	wirelessNetworkPasswordTextLabel->setPalette(descriptionTextPalette);
	wirelessNetworkPasswordTextLabel->setContentsMargins(0, 15, 0, 4); /* padding from line edit above */
	startupWidgetLayout->addWidget(wirelessNetworkPasswordTextLabel, 0, Qt::AlignTop);
	
	//Draw the Wireless Network Password line edit field
	wirelessNetworkPasswordLineEdit = new QLineEdit();
	wirelessNetworkPasswordLineEdit->setText("inssidious");
	startupWidgetLayout->addWidget(wirelessNetworkPasswordLineEdit, 0, Qt::AlignTop);
	
	//Draw the Internet Connection description field
	internetConnectionTextLabel = new QLabel();
	internetConnectionTextLabel->setText(internetConnectionText);
	internetConnectionTextLabel->setPalette(descriptionTextPalette);
	internetConnectionTextLabel->setContentsMargins(0, 15, 0, 4); /* padding from line edit above */
	startupWidgetLayout->addWidget(internetConnectionTextLabel, 0, Qt::AlignTop);

	//Draw the Internet Connection combo box
	internetConnectionComboBox = new QComboBox();
	startupWidgetLayout->addWidget(internetConnectionComboBox, 0, Qt::AlignTop);

	//Fill the Internet Connection Combo Box with internet network adapters
	for (NetworkAdapter networkAdapter : Core::NetworkAdapterList)
	{
		//Add each of them to the Internet Connection combo box
		internetConnectionComboBox->addItem(networkAdapter.AdapterDescription);

	}

	//Draw the Start button
	inssidiousStartButton = new QPushButton();
	inssidiousStartButton->setMinimumSize(QSize(104, 30));
	inssidiousStartButton->setStyleSheet("QPushButton{ border: none; background-image: url(\":/StartupWidget/StartButtonActive.png\"); }QPushButton:!enabled{background-image: url(\":/StartupWidget/StartButtonInactive.png\");}QPushButton:hover{ background-image: url(\":/StartupWidget/StartButtonHover.png\");}QPushButton:pressed{ background-image: url(\":/StartupWidget/StartButtonPressed.png\");}QPushButton:focus { outline: none;}");
	startupWidgetLayout->addSpacing(25); /* padding from line edit above */
	startupWidgetLayout->addWidget(inssidiousStartButton, 0, Qt::AlignCenter);

	//Pad the remaining layout space at the bottom to push content up
	startupWidgetLayout->addStretch();

	//Connect the start button signal & slot
	connect(inssidiousStartButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));

}

void StartupWidget::onStartButtonClicked()
{
	//Bool to abort signaling core if any data is invalid
	bool dataIsValid = true;

	//Reset description texts & palettes
	internetConnectionTextLabel->setText(internetConnectionText);
	internetConnectionTextLabel->setPalette(descriptionTextPalette);
	wirelessNetworkNameTextLabel->setText(wirelessNetworkNameText);
	wirelessNetworkNameTextLabel->setPalette(descriptionTextPalette);
	wirelessNetworkPasswordTextLabel->setText(wirelessNetworkPasswordText);
	wirelessNetworkPasswordTextLabel->setPalette(descriptionTextPalette);

	//Find the index of our selected adapters to emit to core later
	int internetConnectionIndex;
	for (int i = 0; i < Core::NetworkAdapterList.count(); i++)
	{
		if (internetConnectionComboBox->currentText() == Core::NetworkAdapterList[i].AdapterDescription)
		{
			internetConnectionIndex = i;
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
		emit coreStartRouter(wirelessNetworkNameLineEdit->text(), wirelessNetworkPasswordLineEdit->text(), Core::NetworkAdapterList[internetConnectionIndex].AdapterName);
	}

	/* If data did not pass checks, error text is displayed and we can wait for the start button to be clicked again */
}

