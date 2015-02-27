#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>

class DeviceWidget : public QWidget
{
	Q_OBJECT

public:
	DeviceWidget(QWidget *parent);
	void hideDeviceWidget();					//Hide device widget
	void showDeviceWidget();					//Show device widget

signals:
	void deviceWidgetSelected();				//Notify parent of widget selection

public slots:
	void showTamperActivity();					//Draw outer circle to indicate tamper activity
	void updateTamperCounts();					//Increment or decrement tamper count

private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);
};

#endif // DEVICEWIDGET_H
