#include "tamperwidget.h"

TamperWidget::TamperWidget(TamperType tamperType)
{
	//Enable mouse tracking for hover highlighting on the widget
	this->setMouseTracking(true);
	
	//Initialize name, icons, and descriptions
	tamperName = new QLabel();
	tamperIconActive = new QLabel();
	tamperIconInactive = new QLabel();
	tamperDescription = new QLabel();

	//Initialize tamperName font 
	tamperNameFont.setPixelSize(22);
	tamperNameFont.setFamily("Calibri");
	tamperNameFont.setBold(true);
	tamperNameFont.setStyleStrategy(QFont::PreferAntialias);

	//Initialize tamperDescription font
	tamperDescriptionFont.setPixelSize(14);
	tamperDescriptionFont.setFamily("Calibri");
	tamperDescriptionFont.setStyleStrategy(QFont::PreferAntialias);

	//Initialize the tamper text's palettes
	tamperTextsPaletteInactive.setColor(QPalette::WindowText, QColor(107, 107, 107));
	tamperTextsPaletteActive.setColor(QPalette::WindowText, QColor(107, 107, 107));

	//Initialize the background rounded rectangles
	tamperWidgetPaletteActive.setBrush(QPalette::Background, QBrush(QImage(":/TamperWidget/TamperWidgetActive.png")));
	tamperWidgetPaletteInactive.setBrush(QPalette::Background, QBrush(QImage(":/TamperWidget/TamperWidgetInactive.png")));

	//Set the background to inactive and set a fixed size
	this->setPalette(tamperWidgetPaletteInactive);
	this->setAutoFillBackground(true);
	this->setFixedSize(478, 66);

	//Set the Name and Description texts
	tamperName->setText(tamperType.Name);
	tamperName->setFont(tamperNameFont);
	tamperName->setPalette(tamperTextsPaletteInactive);
	tamperName->setContentsMargins(15, 0, 0, 0);
	tamperDescription->setText(tamperType.Description);
	tamperDescription->setFont(tamperDescriptionFont);
	tamperDescription->setPalette(tamperTextsPaletteInactive);
	tamperDescription->setContentsMargins(15, 0, 0, 0);

	//Set the tamper icon size, image, and margins 
	tamperIconActive->setMaximumHeight(44);
	tamperIconActive->setPixmap(tamperType.activeIcon);
	tamperIconActive->setContentsMargins(15, 0, 0, 0);
	tamperIconInactive->setMaximumHeight(44);
	tamperIconInactive->setPixmap(tamperType.inactiveIcon);
	tamperIconInactive->setContentsMargins(15, 0, 0, 0);

	//Initialize layouts for the name and description texts
	descriptionChildLayout = new QVBoxLayout();
	descriptionChildLayout->addWidget(tamperDescription);
	descriptionChildLayout->setMargin(5);
	descriptionChildLayout->setSpacing(5);
	descriptionChildLayout->setContentsMargins(0, 0, 0, 10);

	textContainerLayout = new QVBoxLayout();
	textContainerLayout->addWidget(tamperName);
	textContainerLayout->addLayout(descriptionChildLayout);
	textContainerLayout->setMargin(4);
	textContainerLayout->setSpacing(4);
	textContainerLayout->setContentsMargins(0, 10, 0, 0);

	//Initialize the main tamper widget layout and add widgets to it
	tamperWidgetLayout = new QHBoxLayout();
	tamperWidgetLayout->setMargin(0);
	tamperWidgetLayout->setMargin(0);
	tamperWidgetLayout->addWidget(tamperIconInactive);
	tamperWidgetLayout->addLayout(textContainerLayout, 3);


	//Set widget layout
	this->setLayout(tamperWidgetLayout);

}

TamperWidget::~TamperWidget()
{

}

void TamperWidget::tamperWidgetActivated()
{

}

void TamperWidget::tamperWidgetDeactivated()
{

}

void TamperWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void TamperWidget::mousePressEvent(QMouseEvent *e)
{

}

void TamperWidget::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void TamperWidget::contextMenuEvent(QContextMenuEvent *e)
{

}

void TamperWidget::enterEvent(QEvent *e)
{

}

void TamperWidget::leaveEvent(QEvent *e)
{

}