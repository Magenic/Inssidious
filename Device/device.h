#ifndef DEVICE_H
#define DEVICE_H

#include <QObject> 
#include <QThread>
#include "Widgets\DeviceWidgets\devicewidget.h"
#include "Widgets\TamperWidgets\tamperwidget.h"
#include "Core\types.h"
#include "Core\Tamper\networklag.h"

class Device : public QObject
{
	Q_OBJECT

public:
	Device(QString, QWidget*);				//Device MAC Address and MainAreaWidget pointer
	~Device();

	void select();
	void unselect();

	bool isActive = false;

	QString* MACAddress;
	DeviceWidget* deviceWidget;

	QWidget* tamperWidgetsContainer;

signals:


public slots:
	//void onTamperActivity();

private slots:
	void onTamperWidgetClicked(TamperType);

private:
	QGridLayout* containerLayout;

	typedef struct TamperStyles { TamperWidget* widget; Tamper* tamper; QThread* thread; bool isActive; }TamperStyles;

	TamperStyles* NetworkLag = new TamperStyles{ new TamperWidget(NETWORK_LAG), new TamperNetworkLag(), new QThread(this), false, };
	TamperStyles* DropAllTraffic = new TamperStyles{ new TamperWidget(DROP_ALL_TRAFFIC), new TamperNetworkLag(), new QThread(this), false, };
	TamperStyles* DropNonHttpTraffic = new TamperStyles{ new TamperWidget(DROP_NON_HTTP_TRAFFIC), new TamperNetworkLag(), new QThread(this), false, };
	TamperStyles* RedirectToPortal = new TamperStyles{ new TamperWidget(REDIRECT_TO_PORTAL), new TamperNetworkLag(), new QThread(this), false, };
	TamperStyles* WebServiceError = new TamperStyles{ new TamperWidget(WEB_SERVICE_ERROR), new TamperNetworkLag(), new QThread(this), false, };
	TamperStyles* WebServiceTimeOut = new TamperStyles{ new TamperWidget(WEB_SERVICE_TIME_OUT), new TamperNetworkLag(), new QThread(this), false, };
	TamperStyles* WebServiceEmptyResponses = new TamperStyles{ new TamperWidget(WEB_SERVICE_EMPTY_RESPONSES), new TamperNetworkLag(), new QThread(this), false, };

	int totalActiveTamperCount = 0;

};

#endif // DEVICE_H
