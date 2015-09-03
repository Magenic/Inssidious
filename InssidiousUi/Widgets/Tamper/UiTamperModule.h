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

	QString buttonStyleSheet = 
	   "QPushButton{ margin: 0px; padding: 0px; border: 1px solid #72C55D; border-radius: 2px; background-color: #FDFDFD; color:#444444; font-family: 'Segoe UI'; font-size:11px; font-weight:400; text-decoration:none; }\
		QPushButton:!enabled{ border: 1px solid #ABABAB; background-color: #F0F0F0; color:#B0ADB0; }\
		QPushButton:pressed{ background-color: #64B450; color:#333333;}\
		QPushButton:hover:!pressed{ background-color: #82B678; }\
		QPushButton:on{ background-color: #72C55D; color:#333333;}\
		QPushButton:focus{ outline: none; }";


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
