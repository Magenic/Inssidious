#ifndef UITAMPERSPEED_H
#define UITAMPERSPEED_H

#include "UiTamperModule.h"

class UiTamperSpeed : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperSpeed(QWidget *parent, TamperType tamperType);
	~UiTamperSpeed();

private:
	QLayout* speedLayout;
};

#endif // UITAMPERSPEED_H
