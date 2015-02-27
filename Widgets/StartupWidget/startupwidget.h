#ifndef STARTUPWIDGET_H
#define STARTUPWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>

class StartupWidget : public QWidget
{
	Q_OBJECT

public:
	StartupWidget(QWidget *parent);

signals:

public slots:
	void onCoreStarted();
	void onCoreFailedToStart(QString errorMessage);


private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);

	QGridLayout* startupWidgetLayout;
	QLabel* inssidiousLogo;
};

#endif // STARTUPWIDGET_H
