#ifndef UITAMPERCONDITIONS_H
#define UITAMPERCONDITIONS_H

#include "UiTamperModule.h"
#include <QtWidgets/QSpinBox>

class UiTamperConditions : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperConditions(QWidget *parent, TamperType tamperType);
	~UiTamperConditions();

private:
	QGridLayout* conditionsLayout;

	QLabel* conditionsDescriptionLabel;
	QString conditionsDescriptionText = "Introduce intermittent network problems";

	QLabel* lossLabel;
	QString lossText = "Loss:  ";
	QSpinBox* lossSpinBox;
	QLabel* delayLabel;
	QString delayText = "Delay:  ";
	QSpinBox* delaySpinBox;
	QLabel* corruptionLabel;
	QString corruptionText = "Corrupt:  ";
	QSpinBox* corruptionSpinBox;
	QLabel* tcpResetLabel;
	QString tcpResetText = "Reset:  ";
	QSpinBox* tcpResetSpinBox;

	void toggleState(bool) override;
};

#endif // UITAMPERCONDITIONS_H
