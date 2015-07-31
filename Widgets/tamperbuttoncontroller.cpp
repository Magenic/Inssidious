#include "tamperbuttoncontroller.h"

TamperButtonController::TamperButtonController(QWidget *parent)
	: QWidget(parent)
{
	
	this->setGeometry(200,					//698 pixels in from the left
		16,										//6 pixels plus the title bar height down from the top
		800 - 200 - 16 - 16,								//Use width of the png for qlabel width
		600 - 120 - 16 - 16);								//Use height of the png for qlabel height
	QPalette test;
	test.setBrush(QPalette::Background, 				//Initialize the Tabs palette background
		QBrush(Qt::red));						//With the tabs background image
	this->setPalette(test);							//Set the palette 
	this->setAutoFillBackground(true);		//Don't fill in a background color
	this->setParent(parent->parentWidget());				//Display the widget on top of Inssidious widget

}

TamperButtonController::~TamperButtonController()
{

}
