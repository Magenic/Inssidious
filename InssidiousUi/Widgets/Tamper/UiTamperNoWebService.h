#ifndef UITAMPERNOWEBSERVICE_H
#define UITAMPERNOWEBSERVICE_H

#include "UiTamperModule.h"
#include <QtWidgets/QPushButton>

class UiTamperNoWebService : public UiTamperModule
{
	Q_OBJECT

public:
	UiTamperNoWebService(QWidget *parent, TamperType tamperType);
	~UiTamperNoWebService();

private:
	QGridLayout* noWebServiceLayout;

	QLabel* noWebServiceDescriptionLabel;
	QString noWebServiceDescriptionText = "Test functionality when a service times out";


	int blockedServicesCount = 0;
	QString blockedServiceTextFront = "Blocking ";
	QString blockedServiceTextBack = " Services";
	QPushButton* blockWebServicesButton;
	QPushButton* configWebServicesButton;

	void setActive(bool) override;
};

#endif // UITAMPERNOWEBSERVICE_H
