#ifndef UITAMPERNOINTERNET_H
#define UITAMPERNOINTERNET_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>

class UiTamperNoInternet : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoInternet(QWidget *parent, TamperType tamperType);
	~UiTamperNoInternet();

private:
	QGridLayout* noInternetLayout;
	QLabel* noInternetDescriptionLabel;
	QString noInternetText = "Emulate a local network without internet";

	QLabel* noTrafficDescriptionLabel;
	QString noTrafficDescriptionText = "Local Network: ";
	QPushButton* noTrafficButton;

	QLabel* redirDescriptionLabel;
	QString redirDescriptionText   = "Captive Portal: ";
	QPushButton* redirButton;
	

	void setActive(bool) override;

private slots:
	void onNoTrafficButtonClicked();
};

#endif // UITAMPERNOINTERNET_H
