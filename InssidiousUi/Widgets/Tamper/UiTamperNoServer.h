#ifndef UITAMPERNOSERVER_H
#define UITAMPERNOSERVER_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

class UiTamperNoServer : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoServer(QWidget *parent, TamperType tamperType);
	~UiTamperNoServer();

private:
	QGridLayout* noServerLayout;
	
	QLabel* noServerDescriptionLabel;
	QString noServerDescriptionText = "Test functionality when a server is down";

	QPushButton* noServerButton;

	QLabel* configServersDescriptionLabel;
	QString configServersDescriptionText = "Configure Server Block List: ";
	QPushButton* configServersButton;

	void toggleState(bool) override;
};

#endif // UITAMPERNOSERVER_H
