#ifndef TAMPERWIDGET_H
#define TAMPERWIDGET_H

#include <QtWidgets/QWidget>				//Base of UiTamperModule class
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtWidgets/QLabel>					//QLabel for displaying text and icons
#include <QtGui/QMouseEvent>				//Used to track mouse movements and clicks to update state

#include <InssidiousCore/TamperTypes.h>

class UiTamperModule : public QWidget
{
	Q_OBJECT

public:
	UiTamperModule(QWidget* parent, TamperType tamperType);

	static UiTamperModule* makeUiTamperModule(QWidget* parent, TamperType);



	void select();
	void unselect();

	bool selected;

	QPalette moduleTextPaletteActive;
	QPalette moduleTextPaletteInactive;

	QVBoxLayout* moduleLayout;

signals:
	void tamperButtonClicked(UiTamperModule* signaled, void * tamperData);


private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);


	/* Start with a QVBoxLayout and a Name */
	
	QLabel* moduleNameLabel;			
	QFont moduleNameFont;


	/* Palettes and Pixmaps for the Active/Inactive/Hover/Pressed button states */

	QPalette buttonPaletteActive;
	QPalette buttonPaletteActiveHover;
	QPalette buttonPaletteActivePressed;
	QPalette buttonPaletteInactive;
	QPalette buttonPaletteInactiveHover;
	QPalette buttonPaletteInactivePressed;

	QPixmap buttonImageActive = QPixmap(":/Tamper/TamperButtonActive.png");						//QPixmap for active device tampers 
	QPixmap buttonImageActiveHover = QPixmap(":/Tamper/TamperButtonActiveHover.png");			//QPixmap for active device tampers  while hovered over
	QPixmap buttonImageActivePressed = QPixmap(":/Tamper/TamperButtonActivePressed.png");		//QPixmap for active device tampers while pressed
	QPixmap buttonImageInactive = QPixmap(":/Tamper/TamperButtonInactive.png");					//QPixmap for inactive device tampers 
	QPixmap buttonImageInactiveHover = QPixmap(":/Tamper/TamperButtonInactiveHover.png");		//QPixmap for active device tampers while hovered over
	QPixmap buttonImageInactivePressed = QPixmap(":/Tamper/TamperButtonInactivePressed.png");	//QPixmap for active device tampers while pressed

};

#endif // TAMPERWIDGET_H
