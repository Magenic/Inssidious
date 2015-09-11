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

	QString damageText = "Corrupt: ";
	QSpinBox* damageSpinBox;

	QPushButton* randomizeConditions;


	void setActive(bool) override;


private slots:
	void onRandomizeConditionsClicked();
	void onDamageSpinBoxChange(int value);
};
#endif // UITAMPERDAMAGE_H
