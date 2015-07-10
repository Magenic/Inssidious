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

class Start : public QWidget
{
	Q_OBJECT

public:
	Start(QWidget *parent, QList<QString> networkAdapterDescriptions);
	~Start();


signals:
	//Signal to Inssidious that the user has set a name and password and asked to start
	void startCore(QString networkName, QString networkPassword, QString networkAdapter);


public slots:
	//Receive and display new status messages when signaled
	void onUpdateStatus(QString newStatusMessage, bool error = false);


private slots:
	//React to Start button being clicked and confirm user inputted valid data
	void onStartButtonClicked();


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

	const QString networkNameText = "Specify the name of the Inssidious wireless network:";
	const QString networkPasswordText = "Specify the password for the Inssidious wireless network:";
	const QString internetConnectionText = "Select an Internet Connection:";


	/* Define the Start button */

	QPushButton* startButton;								//Start button
	QString startButtonStyleSheet =							//Style sheet for the background images of the button in different states
		"QPushButton{ border: none; background-image: url(\":/Start/StartButtonActive.png\"); }\
		QPushButton:!enabled{ background-image: url(\":/Start/StartButtonDisabled;.png\");}\
		QPushButton:hover{ background-image: url(\":/Start/StartButtonHover.png\");}\
		QPushButton:pressed{ background-image: url(\":/Start/StartButtonPressed.png\");}\
		QPushButton:focus { outline: none;} "
		;

};

#endif // START_H
