#ifndef STARTUPWIDGET_H
#define STARTUPWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include "core.h"			//Core signals and network adapter information

class StartupWidget : public QWidget
{
	Q_OBJECT

public:
	StartupWidget(QWidget *parent);

signals:
	void inssidiousStart();

public slots:
	void onCoreStarted();
	void onCoreStartFailed(QString errorMessage);
	void onInssidiousStartFailed(QString errorMessage);
	void onStartButtonClicked();

private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);

	QVBoxLayout* startupWidgetLayout;
	QLabel* inssidiousLogo;
	QLabel* inssidiousTagLine;
	QPalette descriptionTextPalette;
	QLabel* internetConnectionText;
	QComboBox* internetConnectionComboBox;
	QLabel* wirelessAdapterText;
	QComboBox* wirelessAdapterComboBox;
	QLabel* wirelessNetworkNameText;
	QLineEdit* wirelessNetworkNameLineEdit;
	QLabel* wirelessNetworkPasswordText;
	QLineEdit* wirelessNetworkPasswordLineEdit;
	QPushButton* inssidiousStartButton;
};

#endif // STARTUPWIDGET_H
