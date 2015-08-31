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

	QPushButton* noWebServiceButton;

	QLabel* configWebServicesDescriptionLabel;
	QString configWebServicesDescriptionText = "Configure Service Block List: ";
	QPushButton* configWebServicesButton;

	void toggleState(bool) override;
};

#endif // UITAMPERNOWEBSERVICE_H
