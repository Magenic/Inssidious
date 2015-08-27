#ifndef UITAMPERDELAY_H
#define UITAMPERDELAY_H

#include "UiTamperModule.h"

class UiTamperDelay : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperDelay(QWidget *parent, TamperType tamperType);
	~UiTamperDelay();

private:
	QLayout* delayLayout;
};

#endif // UITAMPERDELAY_H
