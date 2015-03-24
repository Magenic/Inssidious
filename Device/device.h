#ifndef DEVICE_H
#define DEVICE_H

#include <QObject> 
#include <QThread>
#include <QPushButton>
#include <QLineEdit>
#include <QListView>
#include "Widgets\DeviceWidgets\devicewidget.h"
#include "Widgets\TamperWidgets\tamperwidget.h"
#include "Core\types.h"
#include "Core\Tamper\networklag.h"

class Device : public QObject
{
	Q_OBJECT

public:
	Device(QString, QWidget*);					//Device MAC Address and MainAreaWidget pointer
	~Device();

	void select();								//Set the device sidebar widget as active and show the tamper widgets container
	void unselect();							//Set the device sidebar widget as inactive and hide the tamper widgets container

	bool isActive;								//Track whether or not we're the current active device 

	QString* MACAddress;						//Used for identifying device objects on disconnect notifications from Core's Router
	DeviceWidget* deviceWidget;					//Device sidebar widget, public so InssidiousUi can track clicks

private slots:
	void onTamperWidgetClicked(TamperType);
	void onSetButtonClicked();

private:
	QWidget* tamperWidgetsContainer;			//QWidget that hosts the individual tamper widgets

	QGridLayout* tamperWidgetsContainerLayout;	//QLayout for the individual tamper widgets
	QGridLayout* initialNewDeviceLayout;		//QLayout for getting the initial new device information from the user

	QPushButton* setNewDeviceInfoButton;		//Set QPushButton in the initial new device layout

	QPalette descriptionTextPalette;			//Palette for grey description text
	QPalette errorTextPalette;					//Palette for red error text

	QLabel* deviceNameTextLabel;				//Description text label
	QLineEdit* deviceNameLineEdit;				//Editable field to specify the device name

	QListView* deviceIconImageList;				//List of device icons

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
