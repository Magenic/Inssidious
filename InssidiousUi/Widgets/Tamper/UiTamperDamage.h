#ifndef UITAMPERDAMAGE_H
#define UITAMPERDAMAGE_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

class UiTamperDamage : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperDamage(QWidget *parent, TamperType tamperType);
	~UiTamperDamage();

private:
	QGridLayout* damageLayout;
	QGridLayout* spinboxChildLayout;


	QString damageText =   "Corrupt Data: ";
	QSpinBox* damageSpinBox;
	QString tcpCloseText = "TCP Close: ";
	QSpinBox* tcpCloseSpinBox;


	QPushButton* randomizeConditions;


	void setActive(bool) override;


private slots:
	void onRandomizeConditionsClicked();
	void onDamageSpinBoxChange(int value);
	void onTCPCloseSpinBoxChange(int value);
};
#endif // UITAMPERDAMAGE_H
