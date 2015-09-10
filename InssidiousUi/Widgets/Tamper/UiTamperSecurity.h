#ifndef UITAMPERSECURITY_H
#define UITAMPERSECURITY_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>

class UiTamperSecurity : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperSecurity(QWidget *parent, TamperType tamperType);
	~UiTamperSecurity();

private:
	QGridLayout* securityLayout;


	QPushButton* noTrafficButton;
	QPushButton* redirButton;


	void setActive(bool) override;

private slots:
	void onNoTrafficButtonClicked();
};
#endif // UITAMPERSECURITY_H
