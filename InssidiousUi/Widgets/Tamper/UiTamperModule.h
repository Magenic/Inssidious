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


	/* Used when switching between active/inactive states */

	virtual void setActive(bool) = 0;
	QPalette moduleBackgroundPaletteActive;
	QPalette moduleBackgroundPaletteInactive;


	/* Used by child classes to keep consistent font size and colors */
	
	QFont moduleTextFont;
	QPalette moduleTextPalette;
	

	/* Used by child classes to add their unique widgets to */
	
	QVBoxLayout* moduleLayout;


	/* Used by child classes to pass parameters to InssidiousCore */
	
	void* pTamperConfig;


	/* Used by child classes for displayed buttons */

	QString buttonStyleSheet = 
	   "QPushButton{ margin: 0px; padding: 0px; border: 1px solid #CCCCCC; background-color: #FFFFFF; color:#333333; font-family: 'Segoe UI'; font-size:12px; font-weight:400; text-decoration:none; }\
		QPushButton:!enabled{ border: 1px solid #B0ADB0; background-color: #FFFFFF; color:#B0ADB0; }\
		QPushButton:pressed{ border: 1px solid #72C55D; background-color: #4E9E38; color:#333333;}\
		QPushButton:hover:!pressed{ border: 1px solid #72C55D; background-color: #D5EDCF; }\
		QPushButton:on{ border: 1px solid #72C55D; background-color: #72C55D; color:#333333;}\
		QPushButton:on:hover:!pressed{ border: 1px solid #72C55D; background-color: #50B235; color:#333333; }\
		QPushButton:focus{ outline: none; }";

	QString comboBoxStyleSheet =
		"QComboBox { border: 1px solid #CCCCCC; border-radius: 2px; background-color: #FFFFFF; color:#333333; font-family: 'Segoe UI'; font-size:12px; font-weight:400; text-decoration:none;}\
		 QComboBox:disabled { border: 1px solid #B0ADB0; background-color: #FFFFFF; color:#B0ADB0; }\
		 QComboBox:hover { border: 2px solid #72C55D;}\
		 QComboBox:!editable:hover { border: 2px solid #72C55D;}\
		 QComboBox:on { background-color: #FFFFFF; color:#333333;}\
		 QComboBox::down-arrow:disabled { width: 30px;    height: 30px;	image: url(:/InssidiousUi/DownArrowDisabled.png); }\
		 QComboBox::down-arrow { width: 30px; height: 30px;	image: url(:/InssidiousUi/DownArrow.png);}\
		 QComboBox::drop-down { subcontrol-origin: margin; subcontrol-position: top right; width: 20px; border-style: none; border-image: none;}";

	QString spinBoxStyleSheet = 
		"QSpinBox { margin: 0px; padding: 0px; border: 1px solid #CCCCCC; background-color: #FFFFFF; color:#333333; font-family: 'Segoe UI'; font-size:12px; font-weight:400; text-decoration:none; }\
		 QSpinBox:!enabled{ margin: 0px; padding: 0px; border: 1px solid #B0ADB0; background-color: #FFFFFF; color:#B0ADB0; }";

signals:
	void tamperStart(UiTamperModule* signaled, void * pTamperConfig);
	void tamperStop(UiTamperModule* signaled);


private:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);


	/* Name Font, Name Label and Description Label are private from child classes */
	
	QFont moduleNameFont;
	QLabel* moduleNameLabel;


	/* Palettes and Pixmaps for the Active/Inactive states */

	QPalette moduleBackgroundPaletteActiveHover;
	QPalette moduleBackgroundPaletteActivePressed;
	QPalette moduleBackgroundPaletteInactiveHover;
	QPalette moduleBackgroundPaletteInactivePressed;

	QPixmap moduleImageActive = QPixmap(":/Tamper/TamperModuleActive.png");
	QPixmap moduleImageActiveHover = QPixmap(":/Tamper/TamperModuleActiveHover.png");
	QPixmap moduleImageActivePressed = QPixmap(":/Tamper/TamperModuleActivePressed.png");
	QPixmap moduleImageInactive = QPixmap(":/Tamper/TamperModuleInactive.png");
	QPixmap moduleImageInactiveHover = QPixmap(":/Tamper/TamperModuleInactiveHover.png");
	QPixmap moduleImageInactivePressed = QPixmap(":/Tamper/TamperModuleInactivePressed.png");


};

#endif // TAMPERWIDGET_H
