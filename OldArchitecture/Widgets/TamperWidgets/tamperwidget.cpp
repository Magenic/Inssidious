#include "tamperwidget.h"

TamperWidget::TamperWidget(TamperType t)
{
	//Set what type we are
	tamperType = t;

	//Enable mouse tracking for hover highlighting on the widget
	this->setMouseTracking(true);
	
	//Initialize name, icons, and descriptions
	tamperName = new QLabel();
	tamperIcon = new QLabel();
	tamperIconActive = QPixmap();
	tamperIconInactive = QPixmap();
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
	tamperTextsPaletteActive.setColor(QPalette::WindowText, QColor(31, 31, 31));

	//Initialize the active/inactive rounded rectangle palettes
	tamperWidgetPaletteActive.setBrush(QPalette::Background, QBrush(QImage(":/TamperWidget/TamperWidgetActive.png")));
	tamperWidgetPaletteActiveHover.setBrush(QPalette::Background, QBrush(QImage(":/TamperWidget/TamperWidgetActiveHover.png")));
	tamperWidgetPaletteActivePressed.setBrush(QPalette::Background, QBrush(QImage(":/TamperWidget/TamperWidgetActivePressed.png")));
	tamperWidgetPaletteInactive.setBrush(QPalette::Background, QBrush(QImage(":/TamperWidget/TamperWidgetInactive.png")));
	tamperWidgetPaletteInactiveHover.setBrush(QPalette::Background, QBrush(QImage(":/TamperWidget/TamperWidgetInactiveHover.png")));
	tamperWidgetPaletteInactivePressed.setBrush(QPalette::Background, QBrush(QImage(":/TamperWidget/TamperWidgetInactivePressed.png")));

	//Set the background to inactive and set a fixed size
	this->setPalette(tamperWidgetPaletteInactive);
	this->setAutoFillBackground(true);
	this->setFixedSize(478, 66);

	//Set the tamper icon and text content based on the tamper type
	switch (tamperType)
	{
	case NETWORK_LAG:
		tamperName->setText("Network Lag");
		tamperDescription->setText("Simulates a slow network connection");
		tamperIconActive = QPixmap(":/TamperWidget/NetworkLagActive.png");
		tamperIconInactive = QPixmap(":/TamperWidget/NetworkLagInactive.png");
		break;
	case DROP_ALL_TRAFFIC:
		tamperName->setText("Drop All Traffic");
		tamperDescription->setText("No network traffic can pass in or out");
		tamperIconActive = QPixmap(":/TamperWidget/DropAllTrafficActive.png");
		tamperIconInactive = QPixmap(":/TamperWidget/DropAllTrafficInactive.png");
		break;
	case DROP_NON_HTTP_TRAFFIC:
		tamperName->setText("Drop Non-HTTP Traffic");
		tamperDescription->setText("Only traffic over port 80 and 443 is allowed");
		tamperIconActive = QPixmap(":/TamperWidget/DropNonHTTPTrafficActive.png");
		tamperIconInactive = QPixmap(":/TamperWidget/DropNonHTTPTrafficInactive.png");
		break;
	case REDIRECT_TO_PORTAL:
		tamperName->setText("Redirect To Portal");
		tamperDescription->setText("All traffic is intercepted and redirected to a portal");
		tamperIconActive = QPixmap(":/TamperWidget/RedirectToPortalActive.png");
		tamperIconInactive = QPixmap(":/TamperWidget/RedirectToPortalInactive.png");
		break;
	case WEB_SERVICE_ERROR:
		tamperName->setText("Web Service Error");
		tamperDescription->setText("Simulates web services returning HTTP errors");
		tamperIconActive = QPixmap(":/TamperWidget/WebServiceErrorsActive.png");
		tamperIconInactive = QPixmap(":/TamperWidget/WebServiceErrorsInactive.png");
		break;
	case WEB_SERVICE_TIME_OUT:
		tamperName->setText("Web Service Time Out");
		tamperDescription->setText("Simulates non-responsive web services");
		tamperIconActive = QPixmap(":/TamperWidget/WebServiceTimeoutsActive.png");
		tamperIconInactive = QPixmap(":/TamperWidget/WebServiceTimeoutsInactive.png");
		break;
	case WEB_SERVICE_EMPTY_RESPONSES:
		tamperName->setText("Empty Responses");
		tamperDescription->setText("Simulates web services sending empty responses");
		tamperIconActive = QPixmap(":/TamperWidget/WebServiceEmptyResponsesActive.png");
		tamperIconInactive = QPixmap(":/TamperWidget/WebServiceEmptyResponsesInactive.png");
		break;
	default:
		break;
	}

	//Initialize the tamper activity layout, label, and movie
	tamperActivity = new QLabel();
	tamperActivityMovie = new QMovie(":/TamperWidget/TamperActivity.gif");
	tamperActivity->setContentsMargins(0, 0, 0, 0);
	tamperActivity->setMovie(tamperActivityMovie);
	tamperActivityMovie->setParent(tamperActivity);
	this->tamperActivityMovie->jumpToFrame(0);
	connect(this->tamperActivityMovie, SIGNAL(finished()), this, SLOT(onEndTamperActivity()));

	//Set the tamper icon size, image, and margins 
	tamperIcon->setFixedSize(44, 44);
	tamperIcon->setPixmap(tamperIconInactive);
	tamperIcon->setContentsMargins(0, 0, 0, 0);

	//Set the Name and Description text style and padding 
	tamperName->setFont(tamperNameFont);
	tamperName->setPalette(tamperTextsPaletteInactive);
	tamperName->setContentsMargins(10, 0, 0, 0);
	tamperDescription->setFont(tamperDescriptionFont);
	tamperDescription->setPalette(tamperTextsPaletteInactive);
	tamperDescription->setContentsMargins(10, 0, 0, 0);

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
	tamperWidgetLayout->addSpacing(10);
	tamperWidgetLayout->addWidget(tamperActivity);
	tamperWidgetLayout->addWidget(tamperIcon);
	tamperWidgetLayout->addLayout(textContainerLayout, 3); /* contains name and description text labels */


	//Set widget layout
	this->setLayout(tamperWidgetLayout);

}

void TamperWidget::onTamperActivity()
{
	if (this->tamperActivityMovie->currentFrameNumber() == 0)
	{
		this->tamperActivityMovie->start();
	}
}

void TamperWidget::onEndTamperActivity()
{
	this->tamperActivityMovie->jumpToFrame(0);
}

void TamperWidget::select()
{
	this->setPalette(tamperWidgetPaletteActive);
	this->tamperDescription->setPalette(tamperTextsPaletteActive);
	this->tamperName->setPalette(tamperTextsPaletteActive);
	this->tamperIcon->setPixmap(tamperIconActive);
}

void TamperWidget::unselect()
{
	this->setPalette(tamperWidgetPaletteInactive);
	this->tamperDescription->setPalette(tamperTextsPaletteInactive);
	this->tamperName->setPalette(tamperTextsPaletteInactive);
	this->tamperIcon->setPixmap(tamperIconInactive);
}

void TamperWidget::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background() == tamperWidgetPaletteActivePressed.background())
	{
		this->setPalette(tamperWidgetPaletteActive);
	}
	else if (this->palette().background() == tamperWidgetPaletteInactivePressed.background())
	{
		this->setPalette(tamperWidgetPaletteInactive);
	}

	emit tamperWidgetClicked(tamperType);
}

void TamperWidget::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background() == tamperWidgetPaletteActive.background() || this->palette().background() == tamperWidgetPaletteActiveHover.background())
		{
			this->setPalette(tamperWidgetPaletteActivePressed);
		}
		else if (this->palette().background() == tamperWidgetPaletteInactive.background() || this->palette().background() == tamperWidgetPaletteInactiveHover.background())
		{
			this->setPalette(tamperWidgetPaletteInactivePressed);
		}
	}
}

void TamperWidget::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void TamperWidget::contextMenuEvent(QContextMenuEvent *e)
{

}

void TamperWidget::enterEvent(QEvent *e)
{
	if (this->palette().background() == tamperWidgetPaletteActive.background())
	{
		this->setPalette(tamperWidgetPaletteActiveHover);
	}
	else if (this->palette().background() == tamperWidgetPaletteInactive.background())
	{
		this->setPalette(tamperWidgetPaletteInactiveHover);
	}
}

void TamperWidget::leaveEvent(QEvent *e)
{
	if (this->palette().background() == tamperWidgetPaletteActiveHover.background() || this->palette().background() == tamperWidgetPaletteActivePressed.background())
	{
		this->setPalette(tamperWidgetPaletteActive);
	}
	else if (this->palette().background() == tamperWidgetPaletteInactiveHover.background() || this->palette().background() == tamperWidgetPaletteInactivePressed.background())
	{
		this->setPalette(tamperWidgetPaletteInactive);
	}
}