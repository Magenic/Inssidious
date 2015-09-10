#ifndef UITAMPERSPEED_H
#define UITAMPERSPEED_H

#include "UiTamperModule.h"


#include <QtWidgets/QPushButton>
#include <QtWidgets/QButtonGroup>

class UiTamperSpeed : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperSpeed(QWidget *parent, TamperType tamperType);
	~UiTamperSpeed();

private:
	QGridLayout* speedLayout;


	QButtonGroup* buttonGroup;
	QPushButton* buttonLeft;
	QPushButton* buttonMiddle1;
	QPushButton* buttonMiddle2;
	QPushButton* buttonRight;


	void setActive(bool) override;

private slots:
	void onButtonClicked(int);
};

#endif // UITAMPERSPEED_H
