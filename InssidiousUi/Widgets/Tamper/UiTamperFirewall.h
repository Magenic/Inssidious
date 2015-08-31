#ifndef UITAMPERFIREWALL_H
#define UITAMPERFIREWALL_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>

class UiTamperFirewall : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperFirewall(QWidget *parent, TamperType tamperType);
	~UiTamperFirewall();

private:
	QGridLayout* firewallLayout;

	QLabel* firewallDescriptionLabel;
	QString firewallDescriptionText = "Replicate common firewall restrictions";


	QLabel* httpDescriptionLabel;
	QString httpDescriptionText = "Allow Traffic Over:";
	QPushButton* httpButton;
	QPushButton* httpsButton;


	QLabel* filterDescriptionLabel;
	QString filterDescriptionText = "Website Filtering:";
	QPushButton* filterButton;



	void toggleState(bool) override;
};

#endif // UITAMPERFIREWALL_H
