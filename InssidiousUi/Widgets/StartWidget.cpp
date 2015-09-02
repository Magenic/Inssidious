/*
*  File:		start.cpp
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description: This Start widget is displayed by Inssidious on launch.
*				Wireless Network Name, Password, & the network adapter
*				to use for the internet connection are captured & sent 
*				out as a signal. Inssidious then deletes this widget.
*
*/


#include "StartWidget.h"


StartWidget::StartWidget(QWidget *parent, QList<QString> networkConnectionDescriptions)
	: QWidget(parent)
{

	/* Set the layout and initial settings for the Start widget */

	this->setLayout(new QVBoxLayout());							//Use a Vertical Box Layout
	this->layout()->setSpacing(0);								//Clear the spacing between any child widgets
	this->layout()->setAlignment(Qt::AlignTop);					//Align layout contents at the top of the widget
	this->setGeometry(16,										//Start 16 pixels in from the left to account for extended frame 
		40,														//40 pixels from the top to clear room for the header
		800 - 16 - 16,											//Use width of the parent - 16 to account for extended frame for widget width 
		600 - 40 - 16);											//Use height of the parent - 16 to account for extended frame for widget height
	this->layout()->addItem(new QSpacerItem(0, 70));			//Pad down from the top before any other items are added
	this->setAutoFillBackground(false);							//Don't fill in a background color
	this->setParent(parent);									//Display the widget on top of Inssidious widget
	descriptionTextPalette.setColor(QPalette::WindowText,		//Set the default description Window text 
									QColor(230, 230, 230));		//To a light grey
	errorTextPalette.setColor(QPalette::WindowText,				//Set the error description Window text 
								QColor(255, 150, 0, 255));		//To a bright red


	/* Draw the Inssidious logo */
	
	logo = new QLabel();										//Initialize the QLabel pointer
	logo->setPixmap(logoPixmap);								//Set it to display the Inssidious logo
	this->layout()->addWidget(logo);							//Add it to the Start widget layout
	this->layout()->setAlignment(logo, Qt::AlignHCenter);		//Align the logo in the center of the widget


	/* Draw the Network Name text label and input field */

	networkNameLabel = new QLabel();							//Initialize the QLabel pointer
	networkNameLabel->setText(networkNameText);					//Set the text
	networkNameLabel->setPalette(descriptionTextPalette);		//Set the text color
	networkNameLabel->setContentsMargins(0, 35, 0, 4);			//Pad the label down 35 from the logo and up 4 from the next object
	networkNameLabel->setAlignment(Qt::AlignCenter);			//Center the text within the QLabel
	networkNameInput = new QLineEdit();							//Initialize the QLineEdit pointer
	networkNameInput->setText("Inssidious - Ian");				//Set the text
	networkNameInput->setFixedSize(300, 20);					//Set a fixed size for the field
	networkNameInput->setAlignment(Qt::AlignCenter);			//Center the text within the field
	this->layout()->addWidget(networkNameLabel);				//Add it to the Start widget layout
	this->layout()->addWidget(networkNameInput);				//Add it to the Start widget layout
	this->layout()->setAlignment(networkNameLabel, Qt::AlignHCenter);	//And align it in the center of the widget
	this->layout()->setAlignment(networkNameInput, Qt::AlignHCenter);	//And align it in the center of the widget


	/* Draw the Network Password text label and input field */

	networkPasswordLabel = new QLabel();						//Initialize the QLabel pointer
	networkPasswordLabel->setText(networkPasswordText);			//Set the text
	networkPasswordLabel->setPalette(descriptionTextPalette);	//Set the text color
	networkPasswordLabel->setContentsMargins(0, 15, 0, 4); 		//Pad the label down 15 from the line edit and up 4 from the next object
	networkPasswordLabel->setAlignment(Qt::AlignCenter);		//Center the text within the QLabel
	networkPasswordInput = new QLineEdit();						//Initialize the QLineEdit pointer
	networkPasswordInput->setText("inssidious");				//Set the text
	networkPasswordInput->setFixedSize(300, 20); 				//Set a fixed size for the field
	networkPasswordInput->setAlignment(Qt::AlignCenter);		//Center the text within the field
	this->layout()->addWidget(networkPasswordLabel);			//Add it to the Start widget layout
	this->layout()->addWidget(networkPasswordInput);			//Add it to the Start widget layout
	this->layout()->setAlignment(networkPasswordLabel, Qt::AlignHCenter);	//And align it in the center of the widget
	this->layout()->setAlignment(networkPasswordInput, Qt::AlignHCenter);	//And align it in the center of the widget


	/* Draw the Internet Connection text label and combo box */

	internetConnectionLabel = new QLabel();						//Initialize the QLabel pointer
	internetConnectionLabel->setText(internetConnectionText);	//Set the text
	internetConnectionLabel->setPalette(descriptionTextPalette);//Set the text color
	internetConnectionLabel->setContentsMargins(0, 15, 0, 4); 	//Pad the label down 15 from the line edit and up 4 from the next object
	internetConnectionLabel->setAlignment(Qt::AlignCenter);		//Center the text within the QLabel
	internetConnectionComboBox = new IComboBox();				//Initialize the QComboBox pointer
	internetConnectionComboBox->setFixedWidth(300);				//Set a fixed size for the field
	this->layout()->addWidget(internetConnectionLabel);			//Add it to the Start widget layout
	this->layout()->addWidget(internetConnectionComboBox);		//Add it to the Start widget layout
	this->layout()->setAlignment(internetConnectionLabel, Qt::AlignHCenter);	//And align it in the center of the widget
	this->layout()->setAlignment(internetConnectionComboBox, Qt::AlignHCenter);	//And align it in the center of the widget
	
	
	/* Set QComboBox's LineEdit as editable and read only in order to center the text */

	internetConnectionComboBox->setEditable(true);											
	internetConnectionComboBox->lineEdit()->setReadOnly(true);
	internetConnectionComboBox->lineEdit()->setContentsMargins(18, 0, 0, 0);
	internetConnectionComboBox->lineEdit()->setAlignment(Qt::AlignCenter);					//Only possible when LineEdit is editable
	internetConnectionComboBox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);	//Allows QComboBox to still display dropdown on click


	/* Populate the QComboBox with the network adapter friendly names */

	for (int i = 0; i < networkConnectionDescriptions.count(); i++)
	{
		internetConnectionComboBox->addItem(networkConnectionDescriptions[i]);					//Add the friendly name from the QList
		internetConnectionComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);	//Center the text
	}
	

	/* Draw the Start button */

	startButton = new QPushButton();						//Initialize the Start button pointer
	startButton->setStyleSheet(startButtonStyleSheet);		//Set the style sheet to get the background images for button states
	startButton->setFixedSize(104, 30);						//Set a fixed button size (#s from the dimensions of the button images)
	connect(startButton, SIGNAL(clicked()),					//To react to button clicks, connect the Start button's clicked signal
		this, SLOT(onStartButtonClicked()));				//To the onStartButtonClicked function in this class
	this->layout()->addItem(new QSpacerItem(0, 15));		//Pad down from the internet connection combo box
	this->layout()->addWidget(startButton);					//Add the start button to the Start widget layout
	this->layout()->setAlignment(startButton, Qt::AlignHCenter);	//And align it in the center of the layout
	

	/* No further work is performed until we receive a clicked signal */

}


//React to Start button being clicked and confirm user inputted valid data
void StartWidget::onStartButtonClicked()
{
	
	/* Maintain a bool to track whether any user data is invalid.
	   This allows for multiple input field errors to be presented 
	   to the user in a single press of the Start button. */

	bool invalidDataDetected = false;


	/* Reset the label text and color palettes from any previous errors */ 
	this->networkNameLabel->clear();
	this->networkNameLabel->setText(networkNameText);
	networkPasswordLabel->setText(networkPasswordText);
	internetConnectionLabel->setText(internetConnectionText);
	networkNameLabel->setPalette(descriptionTextPalette);
	networkPasswordLabel->setPalette(descriptionTextPalette);
	internetConnectionLabel->setPalette(descriptionTextPalette);
	

	/* Check whether the Inssidious Wireless Network Name is of appropriate length */

	if (networkNameInput->text().count() < 1 || networkNameInput->text().count() > 32) 
	{
		//The input field is outside of the 1 - 32 valid SSID key length range
		this->networkNameLabel->clear();
		this->networkNameLabel->setText("The wireless network name must be between 1-32 characters:");
		
		networkNameLabel->setPalette(errorTextPalette);
		invalidDataDetected = true;
	}


	/* Check whether the Inssidious Wireless Network Name uses only simple ASCII characters */

	for (QChar c : networkNameInput->text())
	{
		if (c.unicode() < 20 || c.unicode() > 126) 
		{
			//The input field contains characters outside of the 20 - 126 simple ascii character range
			networkNameLabel->setText("Please only use ASCII characters:");
			networkNameLabel->setPalette(errorTextPalette);
			invalidDataDetected = true;
		}
	}


	/* Check whether the Inssidious Wireless Network Password is of appropriate length */

	if (networkPasswordInput->text().count() < 8 || networkPasswordInput->text().count() > 63) 
	{
		//The input field is outside of the 8 - 63 valid SSID key length range
		networkPasswordLabel->setText("The wireless password must be between 8-63 characters:");
		networkPasswordLabel->setPalette(errorTextPalette);
		invalidDataDetected = true;
	}


	/* Check whether the Inssidious Wireless Network Password uses only simple ASCII characters */

	for (QChar c : networkPasswordInput->text())
	{
		if (c.unicode() < 20 || c.unicode() > 126) 
		{
			//The input field contains characters outside of the 20 - 126 simple ascii character range
			networkPasswordLabel->setText("Please only use ASCII characters:");
			networkPasswordLabel->setPalette(errorTextPalette);
			invalidDataDetected = true;
		}
	}


	/* If any data was invalid, error text is displayed and we can wait for the start button to be clicked again */

	if (invalidDataDetected)
		return;


	/* All input data was valid. Clear the layout for status labels */
	this->layout()->removeWidget(networkNameLabel);
	this->layout()->removeWidget(networkNameInput);
	this->layout()->removeWidget(networkPasswordLabel);
	this->layout()->removeWidget(networkPasswordInput);
	this->layout()->removeWidget(internetConnectionLabel);
	this->layout()->removeWidget(internetConnectionComboBox);
	this->layout()->removeWidget(startButton);
	networkNameLabel->hide();
	networkNameInput->hide();
	networkPasswordLabel->hide();
	networkPasswordInput->hide();
	internetConnectionLabel->hide();
	internetConnectionComboBox->hide();
	startButton->hide();


	/* Draw the Status labels */

	statusEventClass = new QLabel();							//Initialize the QLabel pointer
	statusEventClass->setText("Starting...");					//Set the text to 'Starting'
	statusEventClassFont.setPointSize(20);						//Set the text font size 
	statusEventClass->setFont(statusEventClassFont);			//Set the text font
	statusEventClass->setPalette(descriptionTextPalette);		//Set the text color
	statusEventClass->setContentsMargins(0, 96, 0, 4);			//Pad the label down 96 from the logo & 4 from the next object
	statusEventClass->setAlignment(Qt::AlignCenter);			//Center the text within the QLabel
	statusMessage = new QLabel();								//Initialize the QLabel pointer
	statusMessage->setText("");									//Blank the text for now, signals will adjust later
	statusMessage->setPalette(descriptionTextPalette);			//Set the text color
	statusMessage->setAlignment(Qt::AlignCenter);				//Center the text within the QLabel
	this->layout()->addWidget(statusEventClass);				//Add it to the Start widget layout
	this->layout()->addWidget(statusMessage);					//Add it to the Start widget layout
	this->layout()->setAlignment(statusEventClass, Qt::AlignHCenter);	//And align it in the center of the widget
	this->layout()->setAlignment(statusMessage, Qt::AlignHCenter);		//And align it in the center of the widget


	/* Notify Inssidious */

	emit uiStartCore(networkNameInput->text(),			//Network Name
		networkPasswordInput->text(),					//Network Password
		internetConnectionComboBox->currentText());		//Network Connection

	return;

}


//Receive and display new status messages when signaled
void StartWidget::onUiUpdateStartingText(QString messageText, bool isErrorMessage)
{

	/* Adjust the text palette to red text if the new status is an error */

	if (isErrorMessage)
	{
		this->statusMessage->setPalette(errorTextPalette);
	}
	else
	{
		this->statusMessage->setPalette(descriptionTextPalette);
	}


	/* Update the status texts */

	this->statusMessage->setText(messageText);
	this->statusMessage->repaint();
	this->repaint();
	this->parentWidget()->repaint();
}