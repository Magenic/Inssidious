#ifndef UITAMPERDELAY_H
#define UITAMPERDELAY_H

#include "UiTamperModule.h"
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QPushButton>

class UiTamperDelay : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperDelay(QWidget *parent, TamperType tamperType);
	~UiTamperDelay();

private:
	QGridLayout* delayLayout;
	QButtonGroup* qButtonGroup;
	QPushButton* bLow;
	QPushButton* bMid;
	QPushButton* bHigh;
};

#endif // UITAMPERDELAY_H
