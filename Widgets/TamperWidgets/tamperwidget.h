#ifndef TAMPERWIDGET_H
#define TAMPERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>

class TamperWidget : public QWidget
{
	Q_OBJECT

public:

	typedef struct TamperType {
		QString Name;
		QString Description;
		QPixmap activeIcon;
		QPixmap inactiveIcon;
	} TamperType;

	TamperWidget(TamperType);
	~TamperWidget();

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

	QHBoxLayout* tamperWidgetLayout;
	QVBoxLayout* textContainerLayout;
	QVBoxLayout* descriptionChildLayout;

	QLabel* tamperName;
	QLabel* tamperIconActive;
	QLabel* tamperIconInactive;
	QLabel* tamperDescription;
	
	QFont tamperNameFont;
	QFont tamperDescriptionFont;

	QPalette tamperTextsPaletteActive;
	QPalette tamperTextsPaletteInactive;

	QPalette tamperWidgetPaletteActive;
	QPalette tamperWidgetPaletteInactive;

};

#endif // TAMPERWIDGET_H
