#include "tamperbuttoncontroller.h"

TamperButtonController::TamperButtonController(QWidget *parent)
	: QWidget(parent)
{
	
	QGridLayout* layout = new QGridLayout();
	this->setLayout(layout);									//Use a Vertical Box Layout to stack tabs top -> down
	this->layout()->setContentsMargins(0, 0, 0, 0);				//Zero margins for any child widget margins except for a 20 pixel pad from the top
	this->layout()->setSpacing(0);								//Set spacing between child widgets to 8 pixels
	//this->layout()->setAlignment(Qt::AlignTop);					//Align the child widgets up against the the top of the widget
	this->setGeometry(200,										//698 pixels in from the left
		16,														//6 pixels plus the title bar height down from the top
		800 - 200 - 16 - 16,									//Use width of the png for qlabel width
		600 - 120 - 16 - 16);									//Use height of the png for qlabel height
	this->setAutoFillBackground(false);							//Don't fill in a background color
	this->setParent(parent->parentWidget());					//Display the widget on top of Inssidious widget


	TamperButton* tb1 = new TamperButton(this);
	TamperButton* tb2 = new TamperButton(this);
	TamperButton* tb3 = new TamperButton(this);
	TamperButton* tb4 = new TamperButton(this);
	TamperButton* tb5 = new TamperButton(this);
	TamperButton* tb6 = new TamperButton(this);
	TamperButton* tb7 = new TamperButton(this);
	TamperButton* tb8 = new TamperButton(this);

	layout->addWidget(tb1, 0, 0);
	layout->addWidget(tb2, 0, 1);
	layout->addWidget(tb3, 1, 0);
	layout->addWidget(tb4, 1, 1);
	layout->addWidget(tb5, 2, 0);
	layout->addWidget(tb6, 2, 1);
	layout->addWidget(tb7, 3, 0);
	layout->addWidget(tb8, 3, 1);

	connect(tb1, &TamperButton::tamperButtonClicked, this, &TamperButtonController::onTamperButtonClicked);
	connect(tb2, &TamperButton::tamperButtonClicked, this, &TamperButtonController::onTamperButtonClicked);
	connect(tb3, &TamperButton::tamperButtonClicked, this, &TamperButtonController::onTamperButtonClicked);
	connect(tb4, &TamperButton::tamperButtonClicked, this, &TamperButtonController::onTamperButtonClicked);
	connect(tb5, &TamperButton::tamperButtonClicked, this, &TamperButtonController::onTamperButtonClicked);
	connect(tb6, &TamperButton::tamperButtonClicked, this, &TamperButtonController::onTamperButtonClicked);
	connect(tb7, &TamperButton::tamperButtonClicked, this, &TamperButtonController::onTamperButtonClicked);
	connect(tb8, &TamperButton::tamperButtonClicked, this, &TamperButtonController::onTamperButtonClicked);
}

TamperButtonController::~TamperButtonController()
{

}

void TamperButtonController::onTamperButtonClicked(TamperButton* tamperButton)
{
	if (tamperButton->selected)
	{
		/* TODO: Send blocking? signals up the chain */
		/* Ah. How about an inbetween state of changing... */

		/* Change state of button */
		tamperButton->unselect();
	}
	else
	{
		/* TODO: Send blocking? signals up the chain */
		/* Ah. How about an inbetween state of changing... */

		/* Change state of button */

		tamperButton->select();
	}
}