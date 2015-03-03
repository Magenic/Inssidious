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
	void coreStartInssidious();									//Signal to Core to start Inssidious

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
	QLabel* internetConnectionText;							//Description text
	QComboBox* internetConnectionComboBox;					//Combo box populated by a call to core
	QLabel* wirelessAdapterText;							//Description text
	QComboBox* wirelessAdapterComboBox;						//Combo box popluated by a call to core
	QLabel* wirelessNetworkNameText;						//Description text
	QLineEdit* wirelessNetworkNameLineEdit;					//Editable field to specify the wireless network name
	QLabel* wirelessNetworkPasswordText;					//Description text
	QLineEdit* wirelessNetworkPasswordLineEdit;				//Editable field to specify the wireless network password
	QPushButton* inssidiousStartButton;						//Start button
};

#endif // STARTUPWIDGET_H
