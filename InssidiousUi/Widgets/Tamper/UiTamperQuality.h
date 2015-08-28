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
	QLabel* lossLabel;
	QSpinBox* lossSpinBox;
	QLabel* corruptionLabel;
	QSpinBox* corruptionSpinBox;
	QLabel* tcpResetLabel;
	QSpinBox* tcpResetSpinBox;

};

#endif // UITAMPERQUALITY_H
