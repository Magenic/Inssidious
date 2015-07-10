#ifndef STARTUPWIDGET_H
#define STARTUPWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "Core\core.h"			//Core's NetworkAdapterList 
#include "Core\types.h"			//NetworkAdapter type and AdapterPhysType type



class StartupWidget : public QWidget
{
	Q_OBJECT

public:
	StartupWidget(QWidget *parent);

signals:
	void coreStartRouter(QString, QString, QString);		//Signal to Core to start the router

public slots:
	void onCoreReadyToStart();								//Triggered by Core's successful start, now have a list of network adapters 

private slots:
	void onStartButtonClicked();							//Triggered by QPushButton's clicked signal, check the UI data and signal core to start the router

private:
	QVBoxLayout* startupWidgetLayout;						//Layout for the Startup Widget

	QLabel* inssidiousLogo;									//Logo image
	QLabel* inssidiousTagLine;								//Tag line image

	QPalette descriptionTextPalette;						//Palette for grey description text
	QPalette errorTextPalette;								//Palette for red error text
	QPalette lineEditPalette;								//Palette for line edit background and text color

	QLabel* wirelessNetworkNameTextLabel;					//Description text label
	QLineEdit* wirelessNetworkNameLineEdit;					//Editable field to specify the wireless network name

	QLabel* wirelessNetworkPasswordTextLabel;				//Description text label
	QLineEdit* wirelessNetworkPasswordLineEdit;				//Editable field to specify the wireless network password
	
	QLabel* internetConnectionTextLabel;					//Description text label
	QComboBox* internetConnectionComboBox;					//Combo box for all network adapters

	QPushButton* inssidiousStartButton;						//Start button

	//Description text strings to set the labels to
	const QString wirelessNetworkNameText = "Specify the name of the Inssidious wireless network:";			
	const QString wirelessNetworkPasswordText = "Specify the password for the Inssidious wireless network:";
	const QString internetConnectionText = "Select an Internet Connection:";
};

#endif // STARTUPWIDGET_H
