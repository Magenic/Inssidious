#include "NewDeviceWidget.h"


enum DEVICE_TYPES
{
	ANDROID_PHONE,
	ANDROID_TABLET,
	CHROMEBOOK,
	IPHONE,
	IPAD,
	MAC,
	WINDOWS_PHONE,
	WINDOWS_TABLET,
	WINDOWS_PC,
	OTHER,
	NUM_DEVICE_TYPES
};

static const QString DeviceNames[NUM_DEVICE_TYPES]
{
	QString("Android Phone"),
	QString("Android Tablet"),
	QString("Chromebook"),
	QString("iPhone"),
	QString("iPad"),
	QString("Mac"),
	QString("Windows Phone"),
	QString("Windows Tablet"),
	QString("Windows PC"),
	QString("Other")
};

class IComboBox : public QComboBox
{
	Q_OBJECT

public:

	/* Show pop up on all mouseReleaseEvents received by QComboBox */

	void IComboBox::mouseReleaseEvent(QMouseEvent *event)
	{
		IComboBox::showPopup();
	}

};

NewDeviceWidget::NewDeviceWidget(QWidget *parent, QString MACAddress)
	: QWidget(parent)
{

	MAC = MACAddress;
	backgroundPalette.setBrush(QPalette::Background, QBrush(backgroundImage));
	descriptionTextPalette.setColor(QPalette::WindowText, QColor(230, 230, 230));
	errorTextPalette.setColor(QPalette::WindowText,	QColor(255, 150, 0, 255));


	/* Set the layout and initial settings for the New Device widget */

	this->setLayout(new QVBoxLayout());							//Use a Vertical Box Layout
	this->layout()->setSpacing(0);								//Clear the spacing between any child widgets
	this->layout()->setAlignment(Qt::AlignTop);					//Align layout contents at the top of the widget
	this->setAutoFillBackground(true);							//Don't fill in a background color
	this->setPalette(backgroundPalette);
	this->setGeometry(10 /* in */, 108 /* down */, 780 /* width */, 480 /* height */);


	/* Draw the Device Name text label and input field */

	deviceNameLabel = new QLabel();										//Initialize the QLabel pointer
	deviceNameLabel->setText(deviceNameText);							//Set the text
	deviceNameLabel->setPalette(descriptionTextPalette);				//Set the text color
	deviceNameLabel->setContentsMargins(0, 100, 0, 4);					//Pad the label down 100 from the logo and up 4 from the next object
	deviceNameLabel->setAlignment(Qt::AlignCenter);						//Center the text within the QLabel
	deviceNameInput = new QLineEdit();									//Initialize the QLineEdit pointer
	deviceNameInput->setText("");										//Set the text
	deviceNameInput->setFixedSize(200, 20);								//Set a fixed size for the field
	deviceNameInput->setAlignment(Qt::AlignCenter);						//Center the text within the field
	this->layout()->addWidget(deviceNameLabel);							//Add it to the Start widget layout
	this->layout()->addWidget(deviceNameInput);							//Add it to the Start widget layout
	this->layout()->setAlignment(deviceNameLabel, Qt::AlignHCenter);	//And align it in the center of the widget
	this->layout()->setAlignment(deviceNameInput, Qt::AlignHCenter);	//And align it in the center of the widget


	/* Draw the Internet Connection text label and combo box */

	deviceTypeLabel = new QLabel();										//Initialize the QLabel pointer
	deviceTypeLabel->setText(deviceTypeText);							//Set the text
	deviceTypeLabel->setPalette(descriptionTextPalette);				//Set the text color
	deviceTypeLabel->setContentsMargins(0, 20, 0, 4); 					//Pad the label down 20 from the line edit and up 4 from the next object
	deviceTypeLabel->setAlignment(Qt::AlignCenter);						//Center the text within the QLabel
	deviceTypeComboBox = new IComboBox();								//Initialize the QComboBox pointer
	deviceTypeComboBox->setFixedWidth(200);								//Set a fixed size for the field
	this->layout()->addWidget(deviceTypeLabel);							//Add it to the Start widget layout
	this->layout()->addWidget(deviceTypeComboBox);						//Add it to the Start widget layout
	this->layout()->setAlignment(deviceTypeLabel, Qt::AlignHCenter);	//And align it in the center of the widget
	this->layout()->setAlignment(deviceTypeComboBox, Qt::AlignHCenter);	//And align it in the center of the widget


	/* Set QComboBox's LineEdit as editable and read only in order to center the text */

	deviceTypeComboBox->setEditable(true);
	deviceTypeComboBox->lineEdit()->setReadOnly(true);
	deviceTypeComboBox->lineEdit()->setContentsMargins(18, 0, 0, 0);
	deviceTypeComboBox->lineEdit()->setAlignment(Qt::AlignCenter);					//Only possible when LineEdit is editable
	deviceTypeComboBox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);	//Allows QComboBox to still display dropdown on click


	/* Populate the QComboBox with the network adapter friendly names */

	for (int i = 0; i < NUM_DEVICE_TYPES; i++)
	{
		deviceTypeComboBox->addItem(DeviceNames[i]);								//Add the friendly name from the QList
		deviceTypeComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);	//Center the text
	}


	/* Draw the Start button */

	setButton = new QPushButton();							//Initialize the Start button pointer
	setButton->setStyleSheet(setButtonStyleSheet);			//Set the style sheet to get the background images for button states
	setButton->setFixedSize(90, 30);						//Set a fixed button size (#s from the dimensions of the button images)
	setButton->setText("Save");
	connect(setButton, &QPushButton::clicked, this, &NewDeviceWidget::onSetButtonClicked);
	this->layout()->addItem(new QSpacerItem(0, 24));		//Pad down from the internet connection combo box
	this->layout()->addWidget(setButton);					//Add the start button to the Start widget layout
	this->layout()->setAlignment(setButton, Qt::AlignHCenter);	//And align it in the center of the layout


	/* No further work is performed until we receive a clicked signal */
}

NewDeviceWidget::~NewDeviceWidget()
{

}

void NewDeviceWidget::onSetButtonClicked()
{


	//Check whether the Device Name is of appropriate length
	if (deviceNameInput->text().count() < 1 || deviceNameInput->text().count() > 12) //1 - 12 is the valid length range
	{
		deviceNameLabel->setText("The device name must be between 1-12 characters:");
		deviceNameLabel->setPalette(errorTextPalette);
	}
	else
	{
		//Set the device name and type values
		emit setDeviceInfo(MAC, deviceNameInput->text(), deviceTypeComboBox->currentText().remove(" ")); /* remove spaces to line up device types with icon names */

	}

}