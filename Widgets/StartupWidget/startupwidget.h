#ifndef STARTUPWIDGET_H
#define STARTUPWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include "core.h"			//Core network adapter information

class StartupWidget : public QWidget
{
	Q_OBJECT

public:
	StartupWidget(QWidget *parent);

signals:
	void coreStartInssidious();								//Signal to Core to start Inssidious

public slots:
	void onCoreThreadReady();								//Triggered by Core's successful start, can now ask for network adapters and similar
	
private slots:
	void onStartButtonClicked();							//Triggered by QPushButton's clicked signal, emits info to Core to start Inssidious

private:
	QVBoxLayout* startupWidgetLayout;						//Layout for the Startup Widget
	QLabel* inssidiousLogo;									//Logo image
	QLabel* inssidiousTagLine;								//Tag line image
	QLabel* coreStartFailedText;							//Error text
	QPalette descriptionTextPalette;						//Palette for grey description text
	QPalette errorTextPalette;								//Palette for red error text
	QList<Core::NetworkAdapter> lNetworkAdapters;			//QList of all network adapters
	QLabel* internetConnectionTextLabel;					//Description text label
	QLabel* wirelessAdapterTextLabel;						//Description text label
	QLabel* wirelessNetworkNameTextLabel;					//Description text label
	QComboBox* internetConnectionComboBox;					//Combo box populated by a call to core
	QLabel* wirelessNetworkPasswordTextLabel;				//Description text label
	QComboBox* wirelessAdapterComboBox;						//Combo box popluated by a call to core
	QLineEdit* wirelessNetworkNameLineEdit;					//Editable field to specify the wireless network name
	QLineEdit* wirelessNetworkPasswordLineEdit;				//Editable field to specify the wireless network password
	QPushButton* inssidiousStartButton;						//Start button

	//Description text strings to set the labels to
	const QString internetConnectionText = "Select an Internet Connection:";								
	const QString wirelessAdapterText = "Select a Wireless Adapter:";										
	const QString wirelessNetworkNameText = "Specify the name of the Inssidious wireless network:";			
	const QString wirelessNetworkPasswordText = "Specify the password for the Inssidious wireless network:";
};

#endif // STARTUPWIDGET_H
