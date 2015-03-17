#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QMouseEvent>


class DeviceWidget : public QWidget
{
	Q_OBJECT

public:
	DeviceWidget(QString m);					//MAC Address

	void unselect();							//Show as an unselected device widget
	void select();								//Show as the selected device widget


signals:
	void deviceWidgetClicked(DeviceWidget*);	//Signal this device widget was clicked


private:
	void mousePressEvent(QMouseEvent *e);		//Catch mouse click events
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);

	void initializeNameAndIcons(QString m);		//Fill in deviceNameString, iconActive, and iconInactive from MAC Address

	QHBoxLayout deviceWidgetLayout;				//Layout for the device widget
	
	QLabel deviceIcon;
	QLabel deviceName;

	QString deviceNameString;					//QString for device name
	QPixmap iconActive;							//QPixmap for active icon
	QPixmap iconInactive;						//QPixmap for inactive icon

	QFont deviceNameFont;						//Name text font

	QLabel tamperCount;							//Count of active tamper items

	QColor textColorActive;						//QColors for different mouse states
	QColor textColorInactive;
	QColor backgroundColorActive;
	QColor backgroundColorActiveHover;
	QColor backgroundColorActivePressed;
	QColor backgroundColorInactive;
	QColor backgroundColorInactiveHover;
	QColor backgroundColorInactivePressed;
};

#endif // DEVICEWIDGET_H
