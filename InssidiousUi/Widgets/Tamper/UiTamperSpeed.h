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


	QString buttonLeftStyleSheet = "QPushButton { image: url(:/Tamper/ButtonLeftInactive.png); border: none;}QPushButton:hover { image: url(:/Tamper/ButtonLeftInactive.png); border: none;}QPushButton:on { image: url(:/Tamper/ButtonLeftActive.png); border: none;}QPushButton:pressed { image: url(:/Tamper/ButtonLeftActive.png); border: none;}";
	QString buttonMiddleStyleSheet = "QPushButton { image: url(:/Tamper/ButtonMiddleInactive.png); border: none;}QPushButton:hover { image: url(:/Tamper/ButtonMiddleInactive.png); border: none;}QPushButton:on { image: url(:/Tamper/ButtonMiddleActive.png); border: none;}QPushButton:pressed { image: url(:/Tamper/ButtonMiddleActive.png); border: none;}";
	QString buttonRightStyleSheet = "QPushButton { image: url(:/Tamper/ButtonRightInactive.png); border: none;}QPushButton:hover { image: url(:/Tamper/ButtonRightInactive.png); border: none;}QPushButton:on { image: url(:/Tamper/ButtonRightActive.png); border: none;}QPushButton:pressed { image: url(:/Tamper/ButtonRightActive.png); border: none;}";
	QString buttonDoubleWideStyleSheet = "QPushButton { image: url(:/Tamper/ButtonDoubleWideInactive.png); border: none;}QPushButton:hover { image: url(:/Tamper/ButtonDoubleWideInactive.png); border: none;}QPushButton:on { image: url(:/Tamper/ButtonDoubleWideActive.png); border: none;}QPushButton:pressed { image: url(:/Tamper/ButtonDoubleWideActive.png); border: none;}";


	QPushButton* buttonLeft;
	QPushButton* buttonMiddle1;
	QPushButton* buttonMiddle2;
	QPushButton* buttonRight;

	void toggleState(bool) override;

};

#endif // UITAMPERSPEED_H
