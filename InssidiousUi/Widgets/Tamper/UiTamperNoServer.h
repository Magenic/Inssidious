#ifndef UITAMPERNOSERVER_H
#define UITAMPERNOSERVER_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>


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
	int blockedServersCount = 0;
	QString blockedServerFirstItemText = "  Server Count:  ";
	QComboBox* blockedServersComboBox;
	QPushButton* configServersButton;

	void toggleState(bool) override;

private slots:
	void onConfigureServers();
};

#endif // UITAMPERNOSERVER_H
