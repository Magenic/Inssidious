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

	QPushButton* noTrafficButton;
	QPushButton* redirButton;
	

	void setActive(bool) override;

private slots:
	void onNoTrafficButtonClicked();
};

#endif // UITAMPERNOINTERNET_H
