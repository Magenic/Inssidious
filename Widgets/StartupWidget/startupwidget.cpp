#include "startupwidget.h"

StartupWidget::StartupWidget(QWidget *parent)
	: QWidget(parent)
{
	//Initialize and set the layout for StartupWidget
	startupWidgetLayout = new QVBoxLayout();
	startupWidgetLayout->setSpacing(0); 
	startupWidgetLayout->setContentsMargins(225, 120, 225, 0); /* pushes all content into the middle of the window */
	this->setLayout(startupWidgetLayout);

	//Set the size policy and size of StartupWidget
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setMinimumSize(762, 644);

	//Set the background color of the StartupWidget to a grey black
	QPalette startupWidgetPalette(palette());
	startupWidgetPalette.setColor(QPalette::Background, QColor(42, 42, 42, 255));
	this->setAutoFillBackground(true);
	this->setPalette(startupWidgetPalette);

	//Enable mouse tracking for hover highlighting
	this->setMouseTracking(true);

	//Draw the Inssidious logo and add it to the layout
	inssidiousLogo = new QLabel();
	inssidiousLogo->setPixmap(QPixmap(":/StartupWidget/AppLogo.png"));
	startupWidgetLayout->addWidget(inssidiousLogo, 0, Qt::AlignCenter);

	//Draw the Inssidious tag line and add it to the layout
	inssidiousTagLine = new QLabel();
	inssidiousTagLine->setPixmap(QPixmap(":/StartupWidget/AppTagLine.png"));
	startupWidgetLayout->addWidget(inssidiousTagLine, 0, Qt::AlignCenter);

	//Set the description text palette to a light grey 
	descriptionTextPalette.setColor(QPalette::WindowText, QColor("lightGray"));

	//Draw the Internet Connection description field
	internetConnectionText = new QLabel();
	internetConnectionText->setText("Select an internet connection:");
	internetConnectionText->setPalette(descriptionTextPalette);
	internetConnectionText->setContentsMargins(0, 20, 0, 0); /* padding to push away from logo and tag line */
	startupWidgetLayout->addWidget(internetConnectionText, 0, Qt::AlignTop);

	//Draw the Internet Connection combo box
	internetConnectionComboBox = new QComboBox();
	startupWidgetLayout->addWidget(internetConnectionComboBox, 0, Qt::AlignTop);

	//Draw the Wireless Adapter description field
	wirelessAdapterText = new QLabel();
	wirelessAdapterText->setText("Select a wireless adapter:");
	wirelessAdapterText->setPalette(descriptionTextPalette);
	wirelessAdapterText->setContentsMargins(0, 10, 0, 0); /* padding from combo box above */
	startupWidgetLayout->addWidget(wirelessAdapterText, 0, Qt::AlignTop);

	//Draw the Wireless Adapter combo box
	wirelessAdapterComboBox = new QComboBox();
	startupWidgetLayout->addWidget(wirelessAdapterComboBox, 0, Qt::AlignTop);

	//Draw the Wireless Network Name description field
	wirelessNetworkNameText = new QLabel();
	wirelessNetworkNameText->setText("Specify the name of the Inssidious wireless network:");
	wirelessNetworkNameText->setPalette(descriptionTextPalette);
	wirelessNetworkNameText->setContentsMargins(0, 10, 0, 0); /* padding from combo box above */
	startupWidgetLayout->addWidget(wirelessNetworkNameText, 0, Qt::AlignTop);

	//Draw the Wireless Network Name line edit field
	wirelessNetworkNameLineEdit = new QLineEdit();
	wirelessNetworkNameLineEdit->setText("Inssidious - Ian");
	startupWidgetLayout->addWidget(wirelessNetworkNameLineEdit, 0, Qt::AlignTop);

	//Draw the Wireless Network Password description field
	wirelessNetworkPasswordText = new QLabel();
	wirelessNetworkPasswordText->setText("Specify the password for the Inssidious wireless network:");
	wirelessNetworkPasswordText->setPalette(descriptionTextPalette);
	wirelessNetworkPasswordText->setContentsMargins(0, 10, 0, 0); /* padding from line edit above */
	startupWidgetLayout->addWidget(wirelessNetworkPasswordText, 0, Qt::AlignTop);

	//Draw the Wireless Network Password line edit field
	wirelessNetworkPasswordLineEdit = new QLineEdit();
	wirelessNetworkPasswordLineEdit->setText("inssidious");
	startupWidgetLayout->addWidget(wirelessNetworkPasswordLineEdit, 0, Qt::AlignTop);

	//Draw the Start button
	inssidiousStartButton = new QPushButton();
	inssidiousStartButton->setText("Start");
	startupWidgetLayout->addSpacing(10); /* padding from line edit above */
	startupWidgetLayout->addWidget(inssidiousStartButton, 0, Qt::AlignCenter);

	//Pad the remaining layout space at the bottom to push content up
	startupWidgetLayout->addStretch();

	//Connect the start button signal & slot
	connect(inssidiousStartButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
	
}

void StartupWidget::onCoreStarted()
{
	//Get network adapter info

	//Fill in text

	//Un-grey items

}

void StartupWidget::onCoreStartFailed(QString errorMessage)
{
	//Hide or grey normal widgets

	//Show error
}

void StartupWidget::onInssidiousStartFailed(QString errorMessage)
{
	//Hide or grey normal widgets

	//Show error
}


void StartupWidget::onStartButtonClicked()
{
	//Check fields for validity

	//Signal to core to start Inssidious
	emit inssidiousStart(/* put info here */);
}

void StartupWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void StartupWidget::mousePressEvent(QMouseEvent *e)
{

}

void StartupWidget::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void StartupWidget::contextMenuEvent(QContextMenuEvent *e)
{

}

void StartupWidget::enterEvent(QEvent *e)
{

}

void StartupWidget::leaveEvent(QEvent *e)
{

}