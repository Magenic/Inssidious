#ifndef UITAMPERQUALITY_H
#define UITAMPERQUALITY_H

#include "UiTamperModule.h"
#include <QtWidgets/QSpinBox>


class UiTamperQuality : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperQuality(QWidget *parent, TamperType tamperType);
	~UiTamperQuality();

private:
	QGridLayout* qualityLayout;

	void toggleState(bool) override;
};

#endif // UITAMPERQUALITY_H
