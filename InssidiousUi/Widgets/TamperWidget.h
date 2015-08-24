#ifndef TAMPERWIDGET_H
#define TAMPERWIDGET_H

#include <QtWidgets/QWidget>				//Base of TamperWidget class
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtWidgets/QLabel>					//QLabel for displaying text and icons
#include <QtGui/QMouseEvent>				//Used to track mouse movements and clicks to update state

#include <InssidiousCore/TamperTypes.h>

class TamperWidget : public QWidget
{
	Q_OBJECT

public:
	TamperWidget(TamperType tamperType);

	void select();
	void unselect();

	bool selected;

signals:
	void tamperButtonClicked(TamperWidget*);


private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);


	/* QHBoxLayout */
	
	QHBoxLayout* tamperWidgetLayout;


	/* Tamper Palettes and Pixmaps for the Active/Inactive/Hover/Pressed button states */

	QPalette tamperPaletteActive;
	QPalette tamperPaletteActiveHover;
	QPalette tamperPaletteActivePressed;
	QPalette tamperPaletteInactive;
	QPalette tamperPaletteInactiveHover;
	QPalette tamperPaletteInactivePressed;

	QPixmap tamperImageActive = QPixmap(":/Tamper/TamperButtonActive.png");						//QPixmap for active device tampers 
	QPixmap tamperImageActiveHover = QPixmap(":/Tamper/TamperButtonActiveHover.png");			//QPixmap for active device tampers  while hovered over
	QPixmap tamperImageActivePressed = QPixmap(":/Tamper/TamperButtonActivePressed.png");		//QPixmap for active device tampers while pressed
	QPixmap tamperImageInactive = QPixmap(":/Tamper/TamperButtonInactive.png");					//QPixmap for inactive device tampers 
	QPixmap tamperImageInactiveHover = QPixmap(":/Tamper/TamperButtonInactiveHover.png");		//QPixmap for active device tampers while hovered over
	QPixmap tamperImageInactivePressed = QPixmap(":/Tamper/TamperButtonInactivePressed.png");	//QPixmap for active device tampers while pressed


	/* Text QLabels, QFonts, QPalettes, and QPixmaps to draw in the button */

	QLabel* tamperNameLabel;			
	QFont tamperNameFont;

	QLabel* tamperDescriptionLabel;	
	QFont tamperDescriptionFont;

	QPalette tamperTextActive;
	QPalette tamperTextInactive;

	QLabel* tamperIcon;
	QPixmap tamperIconActive;
	QPixmap tamperIconInactive;

};

#endif // TAMPERWIDGET_H
