#ifndef INSSIDIOUS_H
#define INSSIDIOUS_H

#include <QWidget>
#include "ui_inssidious.h"

class Inssidious : public QWidget
{
	Q_OBJECT

public:
	Inssidious(QWidget *parent = 0);
	~Inssidious();


signals:


public slots:
	void showDeviceWidget();					//Hide all device widgets and then show device widget
	void deviceConnected();						//Add a device widget to sidebar
	void deviceDisconnected();					//Remove device widget from sidebar


private:
	Ui::Inssidious ui;
};

#endif // INSSIDIOUS_H