#ifndef TABS_H
#define TABS_H

#include <QtWidgets/QWidget>				//QWidgets
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtGui/QMouseEvent>

class Tab : public QWidget
{
	Q_OBJECT

public:
	Tab(QWidget *parent);

signals:
	void tabClicked(QWidget*);

private:
	void mousePressEvent(QMouseEvent *e);		//Catch mouse click events
	void mouseReleaseEvent(QMouseEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);

	QColor textColorActive;						//QColors for different mouse states
	QColor textColorInactive;
	QColor backgroundColorActive;
	QColor backgroundColorActiveHover;
	QColor backgroundColorActivePressed;
	QColor backgroundColorInactive;
	QColor backgroundColorInactiveHover;
	QColor backgroundColorInactivePressed;
};

class Tabs : public QWidget
{
	Q_OBJECT

public:
	Tabs(QWidget *parent);
	~Tabs();

	void addTab();
	void removeTab();

private:
	QList<Tab*> tabList;
};




#endif // TABS_H
