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
	QPushButton* noServerButton;

	QLabel* domainLabel;
	QComboBox* domainComboBox;
	QPushButton* domainEditButton;
};

#endif // UITAMPERNOSERVER_H
