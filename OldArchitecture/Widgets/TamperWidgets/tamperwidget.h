#ifndef TAMPERWIDGET_H
#define TAMPERWIDGET_H

#include <QWidget>
#include <QMovie>
#include <QLabel>
#include <QLayout>
#include <QMouseEvent>
#include "Core\types.h"

class TamperWidget : public QWidget
{
	Q_OBJECT

public:
	TamperWidget(TamperType);							//Tamper type from types.h
	void select();										//Show as a selected tamper widget
	void unselect();									//Show as an unselected tamper widget


signals: 
	void tamperWidgetClicked(TamperType);				//Signal this tamper widget was clicked

public slots:
	void onTamperActivity();							//Flash the tamper activity label
	void onEndTamperActivity();							//Hide the tamper activity label when done

private:
	void mousePressEvent(QMouseEvent *e);				//Mouse events for hover and select updates
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);

	TamperType tamperType;								//Tamper Type from types.h

	QHBoxLayout* tamperWidgetLayout;					//Layout for the tamper widget
	QVBoxLayout* textContainerLayout;					//Nested layout for the Name and Description
	QVBoxLayout* descriptionChildLayout;				//So much nesting

	QMovie* tamperActivityMovie;						//QMovie to play the activity gif
	
	QLabel* tamperActivity;								//Tamper Activity label
	QLabel* tamperName;									//Tamper Name label
	QLabel* tamperIcon;									//Tamper Icon label
	QLabel* tamperDescription;							//Tamper Description label
	
	QPixmap tamperIconActive;							//Active icon from switch in constructor
	QPixmap tamperIconInactive;							//Inactive icon from switch in constructor

	QFont tamperNameFont;								//Large font size for Name
	QFont tamperDescriptionFont;						//Small font fize for description

	QPalette tamperTextsPaletteActive;					//Dark black text when selected
	QPalette tamperTextsPaletteInactive;				//Light grey text when unselected

	QPalette tamperWidgetPaletteActive;					//Palettes for different hover and select states
	QPalette tamperWidgetPaletteActiveHover;
	QPalette tamperWidgetPaletteActivePressed;
	QPalette tamperWidgetPaletteInactive;
	QPalette tamperWidgetPaletteInactiveHover;
	QPalette tamperWidgetPaletteInactivePressed;
};

#endif // TAMPERWIDGET_H
