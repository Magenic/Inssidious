#ifndef UITAMPERCONDITIONS_H
#define UITAMPERCONDITIONS_H

#include "UiTamperModule.h"
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>

class UiTamperConditions : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperConditions(QWidget *parent, TamperType tamperType);
	~UiTamperConditions();

private:
	QGridLayout* conditionsLayout;
	QGridLayout* spinboxChildLayout;

	QLabel* conditionsDescriptionLabel;
	QString conditionsDescriptionText = "Introduce intermittent network problems";

	
	QString lossText = "Loss: ";
	QString delayText = "Delay: ";
	QString junkText = "Junk: ";
	QString tcpResetText = "Reset: ";
	
	QSpinBox* lossSpinBox;
	QSpinBox* delaySpinBox;
	QSpinBox* junkSpinBox;
	QSpinBox* tcpResetSpinBox;

	QPushButton* randomizeConditions;

	void toggleState(bool) override;


private slots:
	void onRandomizeConditionsClicked();
	void onLossSpinBoxChange(int value);
	void onJunkSpinBoxChange(int value);
	void onDelaySpinBoxChange(int value);
	void onResetSpinBoxChange(int value);

};

#endif // UITAMPERCONDITIONS_H
