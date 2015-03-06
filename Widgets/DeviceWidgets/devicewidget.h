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
	typedef struct DeviceType {
		QString deviceName;
		QPixmap deviceIconActive;
		QPixmap deviceIconInactive;
		int deviceActiveTamperCount;
	} DeviceType;

	DeviceWidget(DeviceType);
	void showAsInactive();						//Hide device widget
	void showAsActive();						//Show device widget

signals:
	void setActiveDeviceWidget();	//Notify Device Object of widget selection

public slots:
	void onShowTamperActivity();				//Draw outer circle to indicate tamper activity
	void onUpdateTamperCounts();				//Increment or decrement tamper count

private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);

	QHBoxLayout deviceWidgetLayout;
	
	QLabel deviceIcon;
	QLabel deviceName;
	QLabel deviceTamperStatusIcon;

	QFont deviceNameFont;

	QColor textColorActive;
	QColor textColorInactive;
	QColor backgroundColorActive;
	QColor backgroundColorActiveHover;
	QColor backgroundColorActivePressed;
	QColor backgroundColorInactive;
	QColor backgroundColorInactiveHover;
	QColor backgroundColorInactivePressed;
};

#endif // DEVICEWIDGET_H
