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
	ConfigureServersDialog(QPoint global, QList<QString> *ipList);

private:
	QGridLayout* dialogGridLayout;

	QLabel* dialogTitle;
	QString dialogTitleText = "Configure Blocked Servers";
	QList<QString> *saveList;
	QPoint global;

	QLabel* listWidgetDescription;
	QListWidget* listWidget;
	QString listWidgetStyleSheet = 
		"QListWidget{ border-width:1px;	border-radius: 2px; border-color: #2D2F31; background-color: #FDFDFD;}";
	/*QListWidget::item { border-style: solid; border-width:1px;	border-color:black; background-color: green; }\
		QListWidget::item:selected { background-color: red; }\*/

	QFont dialogFont;
	QPalette dialogPalette;
	QString dialogStyleSheet =
		"QDialog{ border: 2px solid #72C55D; border-radius: 5px; background-color: #3F4649;}";

	QLabel* dialogInstructions;
	QString dialogInstructionsText = "Add a Domain or IP Address: ";

	QLineEdit* input;

	QPushButton* buttonAdd;
	QPushButton* buttonRemove;
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
