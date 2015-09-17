#ifndef CONFIGUREFIREWALLDIALOG_H
#define CONFIGUREFIREWALLDIALOG_H

#include <QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QComboBox>

class ConfigureFirewallDialog : public QDialog
{
	Q_OBJECT

public:
	ConfigureFirewallDialog(QWidget* parent, QList<int> *portList);

private:
	QList<int> *saveList;


	QGridLayout* dialogGridLayout;
	QFont dialogFont;
	QPalette dialogPalette;
	QPalette dialogErrorPalette;
	QString dialogStyleSheet =
		"QDialog{ margin: 0px; padding: 0px; border: none; background-color: #F0F0F0;}";


	QLabel* dialogTitle;
	QString dialogTitleText = "You can add and remove blocked ports for this device. All ports listed in this list will be not be reachable while enabled.";

	QLabel* inputInstructions;
	QString inputInstructionsText = "Add Ports: ";

	QLineEdit* input;
	QComboBox* presetOptions;

	QLabel* listWidgetDescription;
	QListWidget* listWidget;
	QString listWidgetStyleSheet =
		"QListWidget{ border-style: solid; border-width:1px; border-radius: 0px; border-color: #828790; background-color: #FDFDFD;}";
	//QListWidget::item { border-style: solid; border-width:1px;	border-color:black; background-color: green; }\
			//QListWidget::item:selected { background-color: red; }\


	QPushButton* buttonAddCustom;
	QPushButton* buttonAddPreset;
	QPushButton* buttonRemove;
	QPushButton* buttonClear;
	QPushButton* buttonSave;
	QPushButton* buttonCancel;

private slots:
	void onAddCustom();
	void onAddPreset();
	void onRemove();
	void onClear();
	void onSave();

};


#endif // CONFIGUREFIREWALLDIALOG_H
