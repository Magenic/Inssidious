#ifndef DEVICEOBJECT_H
#define DEVICEOBJECT_H

#include <QObject>
#include "DeviceWidgets\devicewidget.h"
#include "TamperWidgets\tamperwidget.h"

class DeviceObject : public QObject
{
	Q_OBJECT

public:
	DeviceObject(QWidget* scrollAreaWidget, QWidget* mainAreaWidget);
	~DeviceObject();

	bool isActive();													//Returns private bool isActiveDeviceWidget. Used when switching active widgets
	void setActive();													//Instructs the device widget to show as active & shows TamperWidgetsContainer
	void setInactive();													//Instructs the device widget to show as inactive & hides TamperWidgetsContainer

signals:
	void switchDeviceWidgets(DeviceObject*);							//Signals Inssidious to hide all device widgets & show this one

public slots:
	void onSetActiveDeviceWidget();										//Receives a signal from DeviceWidget that it was clicked & should be set as active

private:
	bool isActiveDeviceWidget = false;									//Private active/inactive state
	DeviceWidget* deviceWidget;											//Pointer to the DeviceWidget
	DeviceWidget::DeviceType deviceType;								//DeviceType struct to pass to DeviceWidget
	
	QWidget* tamperWidgetsContainer;									//Pointer to the TamperWidgetsContainer
	QGridLayout tamperWidgetsContainerLayout;							//Layout for TamperWidgetsContainer

	TamperWidget* NetworkLag;											
	TamperWidget* DropAllTraffic;
	TamperWidget* DropNonHttpTraffic;
	TamperWidget* RedirectToPortal;
	TamperWidget* WebServiceError;
	TamperWidget* WebServiceTimeOut;
	TamperWidget* WebServiceEmptyResponses;

	TamperWidget::TamperType NETWORK_LAG = TamperWidget::TamperType { "Network Lag", "Simulates a slow network connection", QPixmap(":/TamperWidget/NetworkLagActive.png"), QPixmap(":/TamperWidget/NetworkLagInactive.png") };
	TamperWidget::TamperType DROP_ALL_TRAFFIC = TamperWidget::TamperType { "Drop All Traffic", "No network traffic can pass in or out", QPixmap(":/TamperWidget/DropAllTrafficActive.png"), QPixmap(":/TamperWidget/DropAllTrafficInactive.png") };
	TamperWidget::TamperType DROP_NON_HTTP_TRAFFIC = TamperWidget::TamperType{ "Drop Non-HTTP Traffic", "Only traffic over port 80 and 443 is allowed", QPixmap(":/TamperWidget/DropNonHTTPTrafficActive.png"), QPixmap(":/TamperWidget/DropNonHTTPTrafficInactive.png") };
	TamperWidget::TamperType REDIRECT_TO_PORTAL = TamperWidget::TamperType { "Redirect To Portal", "All traffic is intercepted and redirected to a portal", QPixmap(":/TamperWidget/RedirectToPortalActive.png"), QPixmap(":/TamperWidget/RedirectToPortalInactive.png") };
	TamperWidget::TamperType WEB_SERVICE_ERROR = TamperWidget::TamperType { "Web Service Error", "Simulates web services returning HTTP errors", QPixmap(":/TamperWidget/WebServiceErrorsActive.png"), QPixmap(":/TamperWidget/WebServiceErrorsInactive.png") };
	TamperWidget::TamperType WEB_SERVICE_TIME_OUT = TamperWidget::TamperType { "Web Service Time Out", "Simulates non-responsive web services", QPixmap(":/TamperWidget/WebServiceTimeoutsActive.png"), QPixmap(":/TamperWidget/WebServiceTimeoutsInactive.png") };
	TamperWidget::TamperType WEB_SERVICE_EMPTY_RESPONSES = TamperWidget::TamperType { "Empty Responses", "Simulates web services sending empty responses", QPixmap(":/TamperWidget/WebServiceEmptyResponsesActive.png"), QPixmap(":/TamperWidget/WebServiceEmptyResponsesInactive.png") };	
};

#endif // DEVICEOBJECT_H
