#ifndef UITAMPERCONTENTBLOCKED_H
#define UITAMPERCONTENTBLOCKED_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

class UiTamperContentBlocked : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperContentBlocked(QWidget *parent, TamperType tamperType);
	~UiTamperContentBlocked();

private:
	QGridLayout* contentBlockedLayout;
	QPushButton* contentBlockedButton;

	QLabel* domainLabel;
	QComboBox* domainComboBox;
	QPushButton* domainEditButton;
};

#endif // UITAMPERCONTENTBLOCKED_H
