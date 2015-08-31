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

	/* Used by TamperWidget to create and check state of the individual tamper modules */

	static UiTamperModule* makeUiTamperModule(QWidget* parent, TamperType);
	void select();
	void unselect();
	bool selected;


	/* Used by child classes to keep consistent font size and colors */
	
	QFont moduleDescriptionFont;
	QPalette moduleTextPaletteActive;
	QPalette moduleTextPaletteInactive;

	/* Used by child classes to add their unique widgets to */
	
	QVBoxLayout* moduleLayout;


	/* Used by child classes to pass parameters to InssidiousCore */
	
	void* pTamperConfig;


	/* Used by child classes for displayed buttons */

	QString buttonLeftStyleSheet = "QPushButton { image: url(:/Tamper/ButtonLeftInactive.png); border: none;}QPushButton:hover { image: url(:/Tamper/ButtonLeftInactive.png); border: none;}QPushButton:on { image: url(:/Tamper/ButtonLeftActive.png); border: none;}QPushButton:pressed { image: url(:/Tamper/ButtonLeftActive.png); border: none;}";
	QString buttonMiddleStyleSheet = "QPushButton { image: url(:/Tamper/ButtonMiddleInactive.png); border: none;}QPushButton:hover { image: url(:/Tamper/ButtonMiddleInactive.png); border: none;}QPushButton:on { image: url(:/Tamper/ButtonMiddleActive.png); border: none;}QPushButton:pressed { image: url(:/Tamper/ButtonMiddleActive.png); border: none;}";
	QString buttonRightStyleSheet = "QPushButton { image: url(:/Tamper/ButtonRightInactive.png); border: none;}QPushButton:hover { image: url(:/Tamper/ButtonRightInactive.png); border: none;}QPushButton:on { image: url(:/Tamper/ButtonRightActive.png); border: none;}QPushButton:pressed { image: url(:/Tamper/ButtonRightActive.png); border: none;}";
	QString buttonDoubleWideStyleSheet = "QPushButton { image: url(:/Tamper/ButtonDoubleWideInactive.png); border: none;}QPushButton:hover { image: url(:/Tamper/ButtonDoubleWideInactive.png); border: none;}QPushButton:on { image: url(:/Tamper/ButtonDoubleWideActive.png); border: none;}QPushButton:pressed { image: url(:/Tamper/ButtonDoubleWideActive.png); border: none;}";


signals:
	void tamperButtonClicked(UiTamperModule* signaled, void * pTamperConfig);


private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);


	/* Name Font, Name Label and Description Label are private from child classes */
	
	QFont moduleNameFont;
	QLabel* moduleNameLabel;


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


	/* Ensure the child classes update as their palettes & states as well */

	virtual void toggleState(bool) = 0;
};

#endif // TAMPERWIDGET_H
