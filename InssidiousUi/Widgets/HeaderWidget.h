/*
*  File:		header.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/

#ifndef HEADER_H
#define HEADER_H

#include <QtWidgets/QWidget>				//QWidgets 
#include <QtWidgets/QLabel>					//QLabel for Sid image
#include <QtWidgets/QPushButton>			//QPushButton for Min Max Close
#include <QtGui/QMouseEvent>				//For mouse over events
#include <QtWinExtras/QtWin>				//For GetSystemMetrics API

class HeaderWidget : public QWidget
{
	Q_OBJECT

public:
	HeaderWidget(QWidget *parent);

private:
	void enterEvent(QEvent *e) override;							
	void leaveEvent(QEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;


	QLabel* sid;													//Sid logo in upper right corner
	QPixmap sidPixmap = QPixmap(":/Header/HeaderSid.png");			//QPixmap for the Sid png

	QPixmap menuDefault = QPixmap(":/Header/MenuDefault.png");		//QPixmap for the Inssidious Menu icon in its default state
	QPixmap menuHover = QPixmap(":/Header/MenuHover.png");			//QPixmap for the Inssidious Menu icon while hovered over
	QPixmap menuPressed = QPixmap(":/Header/MenuPressed.png");		//QPixmap for the Inssidious Menu icon while pressed
	
	QPalette menuPaletteDefault;									//QPalette for Menu png when in its default state
	QPalette menuPaletteHover;										//QPalette for Menu png when hovered over
	QPalette menuPalettePressed;									//QPalette for Menu png when pressed
};

#endif // HEADER_H
