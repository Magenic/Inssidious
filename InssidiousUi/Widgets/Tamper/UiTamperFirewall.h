#ifndef UITAMPERFIREWALL_H
#define UITAMPERFIREWALL_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

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
	QString httpDescriptionText = "Allow Traffic Over: ";
	QComboBox* httpComboBox;


	QLabel* filterDescriptionLabel;
	QString filterDescriptionText = "Website Filtering: ";
	QPushButton* filterButton;

	void toggleState(bool) override;


private slots:

	void onHTTPComboBoxChanged(int index);
	void onFilterButtonClicked();

};

#endif // UITAMPERFIREWALL_H
