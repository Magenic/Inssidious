#ifndef UITAMPERQUALITY_H
#define UITAMPERQUALITY_H

#include "UiTamperModule.h"

class UiTamperQuality : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperQuality(QWidget *parent, TamperType tamperType);
	~UiTamperQuality();

private:
	QLayout* qualityLayout;
};

#endif // UITAMPERQUALITY_H
