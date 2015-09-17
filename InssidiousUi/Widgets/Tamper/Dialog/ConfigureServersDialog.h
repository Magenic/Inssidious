#ifndef CONFIGURESERVERSDIALOG_H
#define CONFIGURESERVERSDIALOG_H

#include <QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QComboBox>

class ConfigureServersDialog : public QDialog
{
	Q_OBJECT

public:
	ConfigureServersDialog(QWidget* parent, QList<QString> *ipList);

private:
	QList<QString> *saveList;


	QGridLayout* dialogGridLayout;
	QFont dialogFont;
	QPalette dialogPalette;
	QString dialogStyleSheet =
		"QDialog{ margin: 0px; padding: 0px; border: none; background-color: #F0F0F0;}";


	QLabel* dialogTitle;
	QString dialogTitleText = "You can add and remove blocked servers for this device. All servers listed in this list will be not be reachable nor heard from while enabled.";
	
	QLabel* inputInstructions;
	QString inputInstructionsText = "Add Servers: ";

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

#endif // CONFIGURESERVERSDIALOG_H
