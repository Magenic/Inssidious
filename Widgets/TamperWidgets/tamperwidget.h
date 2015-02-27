#ifndef TAMPERWIDGET_H
#define TAMPERWIDGET_H

#include <QWidget>

class TamperWidget : public QWidget
{
	Q_OBJECT

public:
	TamperWidget(QWidget *parent);

signals: 
	void activateTamperWidget();
	void deactivateTamperWidget();

public slots: 
	void tamperWidgetActivated();
	void tamperWidgetDeactivated();

private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);
};

#endif // TAMPERWIDGET_H
