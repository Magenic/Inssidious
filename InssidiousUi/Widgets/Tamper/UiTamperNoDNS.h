#ifndef UITAMPERNODNS_H
#define UITAMPERNODNS_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

class UiTamperNoDNS : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoDNS(QWidget *parent, TamperType tamperType);
	~UiTamperNoDNS();

private:
	QGridLayout* noDNSLayout;
	QPushButton* noDNSButton;

	QLabel* domainLabel;
	QComboBox* domainComboBox;
	QPushButton* domainEditButton;

};

#endif // UITAMPERNODNS_H
