#ifndef UITAMPERSPEED_H
#define UITAMPERSPEED_H

#include "UiTamperModule.h"

#include <QtWidgets/QSlider>

class UiTamperSpeed : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperSpeed(QWidget *parent, TamperType tamperType);
	~UiTamperSpeed();

private:
	QGridLayout* speedLayout;
	QSlider *speedSlider;
	QLabel* sliderTextLabel;

	QString sliderString = "  Edge          3g            4g           LTE          Max  ";

private slots:
	void onSpeedSliderChanged(int value);

};

#endif // UITAMPERSPEED_H
