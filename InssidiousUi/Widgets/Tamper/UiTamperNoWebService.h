#ifndef UITAMPERNOWEBSERVICE_H
#define UITAMPERNOWEBSERVICE_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QButtonGroup>

class UiTamperNoWebService : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoWebService(QWidget *parent, TamperType tamperType);
	~UiTamperNoWebService();

private:
	QGridLayout* noWebServiceLayout;

	QPushButton* configWebServicesButton;

	QButtonGroup* buttonGroup;
	QPushButton* buttonLeft;
	QPushButton* buttonMiddle1;
	QPushButton* buttonMiddle2;
	QPushButton* buttonMiddle3;
	QPushButton* buttonRight;


	void setActive(bool) override;

private slots:
	void onButtonClicked(int);
};

#endif // UITAMPERNOWEBSERVICE_H
