/*
*  File:		start.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description: Header file for the Start widget displayed 
*				by Inssidious on launch. Defines the logo,
*				text strings, buttons, & input fields displayed.
*
*/

#ifndef START_H
#define START_H

#include <QtWidgets/QWidget>				//QWidgets 
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtWidgets/QLabel>					//For Inssidious Logo
#include <QtWidgets/QComboBox>				//For available internet connections
#include <QtWidgets/QLineEdit>				//For editable line of text
#include <QtWidgets/QPushButton>			//For Start button

#include <QObject>
#include <QtCore/QEvent>


class StartWidget : public QWidget
{
	Q_OBJECT

public:
	StartWidget(QWidget *parent, QList<QString> networkAdapterDescriptions);


signals:
	//Signal to Inssidious that the user has set a name and password and asked to start
	void uiStartCore(QString networkName, QString networkPassword, QString networkAdapter);


public slots:
	//Receive and display new status messages when signaled
	void onUiUpdateStartingText(QString messageText, bool isErrorMessage = false);


private:

	/* Define the logo displayed at the top of the Start widget */

	QLabel* logo;											//Logo image
	QPixmap logoPixmap = QPixmap(":/Start/StartLogo.png");	//QPixmap for the logo png


	/* Define the Start widget description labels and input fields */

	QPalette descriptionTextPalette;						//Palette for the default grey description text
	QPalette errorTextPalette;								//Palette for red error text if an field has invalid input

	QLabel* networkNameLabel;								//Description text label
	QLabel* internetConnectionLabel;						//Description text label
	QLabel* networkPasswordLabel;							//Description text label

	QLineEdit* networkNameInput;							//Editable field to specify the wireless network name	
	QLineEdit* networkPasswordInput;						//Editable field to specify the wireless network password
	QComboBox* internetConnectionComboBox;					//Combo box for network adapters to use as the internet connection

	QFont statusEventClassFont;								//Font for the event class header text
	QLabel* statusEventClass;								//Status Event Class for Starting, Error, etc.
	QLabel* statusMessage;									//Status message text


	/* Define the description text strings as const QString */

	const QString networkNameText = "Set a name for the Inssidious wireless network:";
	const QString networkPasswordText = "Set a password for the network:";
	const QString internetConnectionText = "Select an Internet Connection:";


	/* Define the Start button */

	QPushButton* startButton;								//Start button
	QString startButtonStyleSheet =							//Style sheet for the background images of the button in different states
	   "QPushButton{ border: 1px solid #72C55D; border-radius: 2px; background-color: #72C55D; color:#333333; font-family: 'Segoe UI Semibold'; font-size:16px; font-weight:400; text-decoration:none; }\
		QPushButton:!enabled{ background-color: #F0F0F0; color:#444444; }\
		QPushButton:pressed{ background-color: #64B450; color:#333333;}\
		QPushButton:hover:!pressed{ background-color: #82B678; }\
		QPushButton:on{ background-color: #72C55D; color:#333333;}\
		QPushButton:focus{ outline: none; }";


private slots:
	//React to Start button being clicked and confirm user inputted valid data
	void onStartButtonClicked();

};


#endif // START_H
