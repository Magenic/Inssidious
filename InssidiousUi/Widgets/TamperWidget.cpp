#include "TamperWidget.h"

TamperWidget::TamperWidget(TamperType tamperType)
{
	/* Initialize tamper palettes for the various button states */

	tamperPaletteActive.setBrush(QPalette::Background, QBrush(tamperImageActive));
	tamperPaletteActiveHover.setBrush(QPalette::Background, QBrush(tamperImageActiveHover));
	tamperPaletteActivePressed.setBrush(QPalette::Background, QBrush(tamperImageActivePressed));
	tamperPaletteInactive.setBrush(QPalette::Background, QBrush(tamperImageInactive));
	tamperPaletteInactiveHover.setBrush(QPalette::Background, QBrush(tamperImageInactiveHover));
	tamperPaletteInactivePressed.setBrush(QPalette::Background, QBrush(tamperImageInactivePressed));

	tamperTextActive.setColor(QPalette::WindowText, QColor(31, 31, 31));
	tamperTextInactive.setColor(QPalette::WindowText, QColor(107, 107, 107));


	/* Set the layout and initial settings */

	tamperWidgetLayout = new QHBoxLayout();
	this->setLayout(tamperWidgetLayout);
	this->setAutoFillBackground(true);
	this->setPalette(tamperPaletteInactive);
	this->setFixedWidth(100);
	this->setFixedHeight(52);
	//this->setParent(parent);
	this->selected = false;


	/* Initialize the Name, Icon, and Description objects */

	tamperNameLabel = new QLabel(TamperTypeName[tamperType]);
	tamperNameFont.setPixelSize(16);
	tamperNameFont.setFamily("Calibri");
	tamperNameFont.setBold(true);
	tamperNameFont.setStyleStrategy(QFont::PreferAntialias);
	tamperNameLabel->setFont(tamperNameFont);
	tamperNameLabel->setPalette(tamperTextInactive);
	tamperNameLabel->setContentsMargins(10, 0, 0, 0);

	tamperDescriptionLabel = new QLabel(TamperTypeDescription[tamperType]);
	tamperDescriptionFont.setPixelSize(12);
	tamperDescriptionFont.setFamily("Calibri");
	tamperDescriptionFont.setStyleStrategy(QFont::PreferAntialias);
	tamperDescriptionLabel->setFont(tamperDescriptionFont);
	tamperDescriptionLabel->setPalette(tamperTextInactive);
	tamperDescriptionLabel->setContentsMargins(10, 0, 0, 0);

	tamperIcon = new QLabel();
	tamperIconActive = QPixmap(TamperTypeInactiveIcon[tamperType]);
	tamperIconInactive = QPixmap(TamperTypeInactiveIcon[tamperType]);
	tamperIcon->setFixedSize(44, 44);
	tamperIcon->setPixmap(tamperIconInactive);
	tamperIcon->setContentsMargins(0, 0, 0, 0);









	
	QVBoxLayout* textContainerLayout;					//Nested layout for the Name and Description
	QVBoxLayout* descriptionChildLayout;				//So much nesting

	//Initialize layouts for the name and description texts
	descriptionChildLayout = new QVBoxLayout();
	descriptionChildLayout->addWidget(tamperDescriptionLabel);
	descriptionChildLayout->setMargin(5);
	descriptionChildLayout->setSpacing(5);
	descriptionChildLayout->setContentsMargins(0, 0, 0, 10);

	textContainerLayout = new QVBoxLayout();
	textContainerLayout->addWidget(tamperNameLabel);
	textContainerLayout->addLayout(descriptionChildLayout);
	textContainerLayout->setMargin(4);
	textContainerLayout->setSpacing(4);
	textContainerLayout->setContentsMargins(0, 10, 0, 0);

	//Initialize the main tamper widget layout and add widgets to it
	tamperWidgetLayout->setMargin(0);
	tamperWidgetLayout->addSpacing(10);
	//tamperWidgetLayout->addWidget(tamperIcon);
	tamperWidgetLayout->addLayout(textContainerLayout); /* contains name and description text labels */


}


void TamperWidget::select()
{
	this->setPalette(tamperPaletteActive);
	this->tamperNameLabel->setPalette(tamperTextActive);
	this->tamperDescriptionLabel->setPalette(tamperTextActive);
	this->tamperIcon->setPixmap(tamperIconActive);
	this->selected = true;
}


void TamperWidget::unselect()
{
	this->setPalette(tamperPaletteInactive);
	this->tamperNameLabel->setPalette(tamperTextInactive);
	this->tamperDescriptionLabel->setPalette(tamperTextInactive);
	this->tamperIcon->setPixmap(tamperIconInactive);
	this->selected = false;
}


void TamperWidget::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background() == tamperPaletteActivePressed.background())
	{
		this->setPalette(tamperPaletteActive);
	}
	else if (this->palette().background() == tamperPaletteInactivePressed.background())
	{
		this->setPalette(tamperPaletteInactive);
	}

	emit tamperButtonClicked(this);
}

void TamperWidget::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background() == tamperPaletteActive.background() || this->palette().background() == tamperPaletteActiveHover.background())
		{
			this->setPalette(tamperPaletteActivePressed);
		}
		else if (this->palette().background() == tamperPaletteInactive.background() || this->palette().background() == tamperPaletteInactiveHover.background())
		{
			this->setPalette(tamperPaletteInactivePressed);
		}
	}
}


void TamperWidget::enterEvent(QEvent *e)
{
	if (this->palette().background() == tamperPaletteActive.background())
	{
		this->setPalette(tamperPaletteActiveHover);
	}
	else if (this->palette().background() == tamperPaletteInactive.background())
	{
		this->setPalette(tamperPaletteInactiveHover);
	}
}


void TamperWidget::leaveEvent(QEvent *e)
{
	if (this->palette().background() == tamperPaletteActiveHover.background() || this->palette().background() == tamperPaletteActivePressed.background())
	{
		this->setPalette(tamperPaletteActive);
	}
	else if (this->palette().background() == tamperPaletteInactiveHover.background() || this->palette().background() == tamperPaletteInactivePressed.background())
	{
		this->setPalette(tamperPaletteInactive);
	}
}