#ifndef TAMPERBUTTON_H
#define TAMPERBUTTON_H

#include <QtWidgets/QWidget>				//Base of TamperButton class
#include <QtWidgets/QLayout>				//Layouts for QWidgets
#include <QtWidgets/QLabel>					//QLabel for displaying text and icons
#include <QtGui/QMouseEvent>				//Used to track mouse movements and clicks to update state


class TamperButton : public QWidget
{
	Q_OBJECT

public:
	TamperButton(QWidget *parent);
	~TamperButton();

	void select();
	void unselect();

	bool selected;

signals:
	void tamperButtonClicked(TamperButton*);


private:
	void mousePressEvent(QMouseEvent *e);		//Catch mouse click events
	void mouseReleaseEvent(QMouseEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);



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


};

#endif // TAMPERBUTTON_H
