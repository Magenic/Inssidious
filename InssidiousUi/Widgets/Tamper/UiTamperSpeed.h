#ifndef UITAMPERSPEED_H
#define UITAMPERSPEED_H

#include "UiTamperModule.h"


#include <QtWidgets/QPushButton>

class UiTamperSpeed : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperSpeed(QWidget *parent, TamperType tamperType);
	~UiTamperSpeed();

private:
	QGridLayout* speedLayout;

	QLabel* speedDescriptionLabel;
	QString speedDescriptionText = "Cap the speed of the network connection";

	QPushButton* buttonLeft;
	QPushButton* buttonMiddle1;
	QPushButton* buttonMiddle2;
	QPushButton* buttonRight;

	void toggleState(bool) override;

};

#endif // UITAMPERSPEED_H
