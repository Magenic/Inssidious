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

	QLabel* speedDescriptionLabel;
	QString speedDescriptionText = "Cap the speed of the network connection";


	QString buttonLeftStyleSheet = 
		"QPushButton { margin: 0px; padding: 0px; color:#333333; font-family: 'Segoe UI'; font-size:12px; font-weight:400; text-decoration:none;image: url(:/Tamper/ButtonLeftInactive.png); border: none;}\
		QPushButton:!enabled { image: url(:/Tamper/ButtonLeftDisabled.png); border: none;color:#B0ADB0;}\
		QPushButton:hover:!pressed { image: url(:/Tamper/ButtonLeftInactiveHover.png); border: none;}\
		QPushButton:on { image: url(:/Tamper/ButtonLeftActive.png); border: none;}\
		QPushButton:on:hover:!pressed{ image: url(:/Tamper/ButtonLeftActiveHover.png); border: none;}\
		QPushButton:pressed{ image: url(:/Tamper/ButtonLeftPressed.png); border: none;}";
	QString buttonMiddleStyleSheet = 
		"QPushButton { margin: 0px; padding: 0px; color:#333333; font-family: 'Segoe UI'; font-size:12px; font-weight:400; text-decoration:none;image: url(:/Tamper/ButtonMiddleInactive.png); border: none;}\
		QPushButton:!enabled { image: url(:/Tamper/ButtonMiddleDisabled.png); border: none;color:#B0ADB0;}\
		QPushButton:hover:!pressed { image: url(:/Tamper/ButtonMiddleInactiveHover.png); border: none;}\
		QPushButton:on { image: url(:/Tamper/ButtonMiddleActive.png); border: none;}\
		QPushButton:on:hover:!pressed { image: url(:/Tamper/ButtonMiddleActiveHover.png); border: none;}\
		QPushButton:pressed { image: url(:/Tamper/ButtonMiddlePressed.png); border: none;}";
	QString buttonRightStyleSheet = 
		"QPushButton { margin: 0px; padding: 0px; color:#333333; font-family: 'Segoe UI'; font-size:12px; font-weight:400; text-decoration:none;image: url(:/Tamper/ButtonRightInactive.png); border: none;}\
		QPushButton:!enabled { image: url(:/Tamper/ButtonRightDisabled.png); border: none;color:#B0ADB0;}\
		QPushButton:hover { image: url(:/Tamper/ButtonRightInactiveHover.png); border: none;}\
		QPushButton:on { image: url(:/Tamper/ButtonRightActive.png); border: none;}\
		QPushButton:on:hover:!pressed { image: url(:/Tamper/ButtonRightActiveHover.png); border: none;}\
		QPushButton:pressed { image: url(:/Tamper/ButtonRightPressed.png); border: none;}";


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
