#ifndef CONFIGURESERVERSDIALOG_H
#define CONFIGURESERVERSDIALOG_H

#include <QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>

class ConfigureServersDialog : public QDialog
{
	Q_OBJECT

public:
	ConfigureServersDialog(QWidget* parent, QList<QString> *ipList);

private:
	QGridLayout* dialogGridLayout;

	QLabel* dialogTitle;
	QString dialogTitleText = "You can add and remove blocked servers for this device. All servers listed in this list will be not be reachable nor heard from while enabled.";
	QList<QString> *saveList;
	QPoint global;

	QLabel* listWidgetDescription;
	QListWidget* listWidget;
	QString listWidgetStyleSheet =
		"QListWidget{ border-style: solid; border-width:1px; border-radius: 0px; border-color: #828790; background-color: #FDFDFD;}";
	/*QListWidget::item { border-style: solid; border-width:1px;	border-color:black; background-color: green; }\
		QListWidget::item:selected { background-color: red; }\*/

	QFont dialogFont;
	QPalette dialogPalette;
	QString dialogStyleSheet =
		"QDialog{ margin: 0px; padding: 0px; border: none; background-color: #F0F0F0;}";

	QLabel* dialogInstructions;
	QString dialogInstructionsText = "Add Servers: ";

	QLineEdit* input;

	QPushButton* buttonAdd;
	QPushButton* buttonRemove;
	QPushButton* buttonClear;
	QPushButton* buttonSave;
	QPushButton* buttonCancel;

public slots:
	void showEvent(QShowEvent* e) override;

private slots:
	void onAdd();
	void onRemove();
	void onSave();

	
};

#endif // CONFIGURESERVERSDIALOG_H
