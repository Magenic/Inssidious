#ifndef UITAMPERWEBSERVICEFAILURES_H
#define UITAMPERWEBSERVICEFAILURES_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QButtonGroup>

class UiTamperWebServiceFailures : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperWebServiceFailures(QWidget *parent, TamperType tamperType);


private:
	QGridLayout* webServiceFailuresLayout;

	QPushButton* configWebServicesButton;

	QButtonGroup* buttonGroup;
	QPushButton* buttonLeft;
	QPushButton* buttonMiddle1;
	QPushButton* buttonMiddle2;
	QPushButton* buttonRight;


	void setActive(bool) override;

private slots:
	void onButtonClicked(int);
};

#endif // UITAMPERWEBSERVICEFAILURES_H
