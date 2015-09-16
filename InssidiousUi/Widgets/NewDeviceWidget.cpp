#include "NewDeviceWidget.h"

#include "Windows.h"

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
	QString("Other"),
	QString("Android Phone"),
	QString("Android Tablet"),
	QString("Chromebook"),
	QString("iPhone"),
	QString("iPad"),
	QString("Mac"),
	QString("Windows Phone"),
	QString("Windows Tablet"),
	QString("Windows PC")
};

class NComboBox : public QComboBox
{

public:

	/* Show pop up on all mouseReleaseEvents received by QComboBox */

	void NComboBox::mouseReleaseEvent(QMouseEvent *event)
	{
		NComboBox::showPopup();
	}

};

NewDeviceWidget::NewDeviceWidget(QWidget *parent, QString MACAddress)
	: QWidget(parent)
{

	MAC = MACAddress;
	backgroundPalette.setBrush(QPalette::Background, QColor(255, 255, 255));
	descriptionTextPalette.setColor(QPalette::WindowText, QColor(230, 230, 230));
	errorTextPalette.setColor(QPalette::WindowText,	QColor(255, 150, 0, 255));


	/* Set the layout and initial settings for the New Device widget */

	this->setLayout(new QVBoxLayout());							//Use a Vertical Box Layout
	this->layout()->setSpacing(0);								//Clear the spacing between any child widgets
	this->layout()->setAlignment(Qt::AlignTop);					//Align layout contents at the top of the widget
	this->setAutoFillBackground(true);							//Don't fill in a background color
	this->setPalette(backgroundPalette);
	this->setGeometry(1 /* in */, 100 /* down */, 798 /* width */, 539 /* height */);


	/* Draw the Device Name text label and input field */

	deviceNameLabel = new QLabel();										//Initialize the QLabel pointer
	deviceNameLabel->setText(deviceNameText);							//Set the text
	deviceNameLabel->setFont(QFont("Segoe UI", 12));
	deviceNameLabel->setPalette(descriptionTextPalette);				//Set the text color
	deviceNameLabel->setContentsMargins(0, 100, 0, 6);					//Pad the label down 100 from the logo and up 4 from the next object
	deviceNameLabel->setAlignment(Qt::AlignCenter);						//Center the text within the QLabel
	deviceNameInput = new QLineEdit();									//Initialize the QLineEdit pointer
	deviceNameInput->setText("");										//Set the text
	deviceNameInput->setFont(QFont("Segoe UI", 10));
	deviceNameInput->setFixedWidth(200);								//Set a fixed size for the field
	deviceNameInput->setAlignment(Qt::AlignCenter);						//Center the text within the field
	this->layout()->addWidget(deviceNameLabel);							//Add it to the Start widget layout
	this->layout()->addWidget(deviceNameInput);							//Add it to the Start widget layout
	this->layout()->setAlignment(deviceNameLabel, Qt::AlignHCenter);	//And align it in the center of the widget
	this->layout()->setAlignment(deviceNameInput, Qt::AlignHCenter);	//And align it in the center of the widget


	/* Draw the Internet Connection text label and combo box */

	deviceTypeLabel = new QLabel();										//Initialize the QLabel pointer
	deviceTypeLabel->setText(deviceTypeText);							//Set the text
	deviceTypeLabel->setFont(QFont("Segoe UI", 12));
	deviceTypeLabel->setPalette(descriptionTextPalette);				//Set the text color
	deviceTypeLabel->setContentsMargins(0, 20, 0, 6); 					//Pad the label down 20 from the line edit and up 4 from the next object
	deviceTypeLabel->setAlignment(Qt::AlignCenter);						//Center the text within the QLabel
	deviceTypeComboBox = new NComboBox();								//Initialize the QComboBox pointer
	deviceTypeComboBox->setFixedWidth(200);								//Set a fixed size for the field
	deviceTypeComboBox->setFont(QFont("Segoe UI", 10));
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
	this->layout()->addItem(new QSpacerItem(0, 30));		//Pad down from the internet connection combo box
	this->layout()->addWidget(setButton);					//Add the start button to the Start widget layout
	this->layout()->setAlignment(setButton, Qt::AlignHCenter);	//And align it in the center of the layout




	/* Open a handle to the Inssidious Registry key and read in known device names and types */
	bool haveName = false;
	bool haveType = false;
	HKEY inssidiousDevicePairsHKCU;
	if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Inssidious\\DevicePairs", 0, 0, 0, KEY_WRITE | KEY_QUERY_VALUE, 0, &inssidiousDevicePairsHKCU, 0))
	{
		DWORD numValues = 0;
		if (ERROR_SUCCESS == RegQueryInfoKey(inssidiousDevicePairsHKCU, 0, 0, 0, 0, 0, 0, &numValues, 0, 0, 0, 0))
		{
			for (int i = 0; i < numValues; i++)
			{
				wchar_t valueName[MAX_PATH];
				wchar_t valueData[MAX_PATH];
				DWORD valueNameCount = MAX_PATH;
				DWORD valueDataCount = MAX_PATH;

				HRESULT result = RegEnumValue(inssidiousDevicePairsHKCU, i, valueName, &valueNameCount, 0, 0, (LPBYTE)valueData, &valueDataCount);

				if (result == ERROR_SUCCESS || result == ERROR_MORE_DATA)
				{
					if (QString::fromWCharArray(valueName) == (MAC + "-Name"))
					{
						deviceNameInput->setText(QString::fromWCharArray(valueData, valueDataCount/2));
						haveName = true;
					}
					else if (QString::fromWCharArray(valueName) == (MAC + "-Type"))
					{
						deviceTypeComboBox->setCurrentText(QString::fromWCharArray(valueData, valueDataCount/2));
						haveType = true;
					}
				}
			}


			if (haveName && haveType)
			{
				knownDevice = true;
				knownDeviceName = deviceNameInput->text();
				knownDeviceType = deviceTypeComboBox->currentText();
			}
		}
	}

	/* No further work is performed until we receive a clicked signal */

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
		 
		/* Save this Device Name and Type to the Registry */

		HKEY inssidiousHKCU;
		if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Inssidious\\DevicePairs", 0, 0, 0, KEY_WRITE, 0, &inssidiousHKCU, 0))
		{
			RegSetValueEx(
				inssidiousHKCU,
				QString(MAC + "-Name").toStdWString().c_str(),
				0,
				REG_SZ,
				(LPBYTE)deviceNameInput->text().utf16(),
				deviceNameInput->text().size() * sizeof(wchar_t)
			);


			RegSetValueEx(
				inssidiousHKCU,
				QString(MAC + "-Type").toStdWString().c_str(),
				0,
				REG_SZ,
				(LPBYTE)deviceTypeComboBox->currentText().utf16(),
				deviceTypeComboBox->currentText().size() * sizeof(wchar_t)
				);
		}


		/* Send out the name and type values */

		emit setDeviceInfo(MAC, deviceNameInput->text(), deviceTypeComboBox->currentText());

	}

}