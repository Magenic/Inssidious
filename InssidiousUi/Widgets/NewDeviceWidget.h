#ifndef NEWDEVICEWIDGET_H
#define NEWDEVICEWIDGET_H

#include <QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>



class NewDeviceWidget : public QWidget
{
	Q_OBJECT

public:
	NewDeviceWidget(QWidget *parent, QString MACAddress);
	~NewDeviceWidget();

signals:
	void setDeviceInfo(QString MACAddress, QString deviceName, QString deviceType);


private:
	QVBoxLayout* ndLayout;

	QString MAC;

	QPalette backgroundPalette;
	QPixmap backgroundImage = QPixmap(":/Tamper/TamperWidgetBackground.png");


	/* Define the description labels and input fields */

	QPalette descriptionTextPalette;						//Palette for the default grey description text
	QPalette errorTextPalette;								//Palette for red error text if an field has invalid input

	QLabel* deviceNameLabel;								//Description text label
	QLabel* deviceTypeLabel;								//Description text label

	QLineEdit* deviceNameInput;								//Editable field to specify the wireless network name	
	QComboBox* deviceTypeComboBox;							//Combo box for network adapters to use as the internet connection


	/* Define the description text strings as const QString */

	const QString deviceNameText = "Set the name of this Device:";
	const QString deviceTypeText = "Select the type of device:";


	/* Define the Start button */

	QPushButton* setButton;									//Set button
	QString setButtonStyleSheet =							//Style sheet for the background colors of the button in different states
		"QPushButton{ border: 1px solid #72C55D; border-radius: 2px; background-color: #72C55D; color:#333333; font-family: 'Segoe UI Semibold'; font-size:15px; font-weight:400; text-decoration:none; }\
		QPushButton:!enabled{ background-color: #F0F0F0; color:#444444; }\
		QPushButton:pressed{ background-color: #64B450; color:#333333;}\
		QPushButton:hover{ background-color: #82B678; }\
		QPushButton:on{ background-color: #72C55D; color:#333333;}\
		QPushButton:focus{ outline: none; }";


private slots:
	//React to Set button being clicked and confirm user inputted valid data
	void onSetButtonClicked();

};


#endif // NEWDEVICEWIDGET_H
