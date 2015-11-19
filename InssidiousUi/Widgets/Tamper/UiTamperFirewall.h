#ifndef UITAMPERFIREWALL_H
#define UITAMPERFIREWALL_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QButtonGroup>

class UiTamperFirewall : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperFirewall(QWidget *parent, TamperType tamperType);

private:
	QGridLayout* firewallLayout;

	QButtonGroup* buttonGroup;
	QPushButton* buttonLeft;
	QPushButton* buttonMiddle1;
	QPushButton* buttonMiddle2;
	QPushButton* buttonRight;

	QList<unsigned short> dialogPortList;
	unsigned short portListVersion;
	
	void setActive(bool) override;

	int lastChecked = -1;

private slots:
	void onButtonClicked(int index);

};

#endif // UITAMPERFIREWALL_H
