#include "UiTamperModule.h"

#include "UiTamperContentBlocked.h"
#include "UiTamperDelay.h"
#include "UiTamperHTTPCorruptedResponse.h"
#include "UiTamperHTTPHTTPSOnly.h"
#include "UiTamperHTTPTimeOut.h"
#include "UiTamperHTTPUnexpectedResponse.h"
#include "UiTamperNoDNS.h"
#include "UiTamperNoInternet.h"
#include "UiTamperNoServer.h"
#include "UiTamperQuality.h"
#include "UiTamperRedirToPortal.h"
#include "UiTamperSpeed.h"


UiTamperModule::UiTamperModule(QWidget* parent, TamperType tamperType)
	: QWidget(parent)
{

	/* Set the layout and initial settings */

	moduleLayout = new QVBoxLayout();
	moduleLayout->setMargin(0);
	moduleLayout->setSpacing(0);
	moduleLayout->setAlignment(Qt::AlignTop);
	
	this->setLayout(moduleLayout);
	this->setFixedWidth(226);
	this->setFixedHeight(70);
	this->setAutoFillBackground(true);


	/* Initialize the button palettes for the various states */

	buttonPaletteActive.setBrush(QPalette::Background, QBrush(buttonImageActive));
	buttonPaletteActiveHover.setBrush(QPalette::Background, QBrush(buttonImageActiveHover));
	buttonPaletteActivePressed.setBrush(QPalette::Background, QBrush(buttonImageActivePressed));
	buttonPaletteInactive.setBrush(QPalette::Background, QBrush(buttonImageInactive));
	buttonPaletteInactiveHover.setBrush(QPalette::Background, QBrush(buttonImageInactiveHover));
	buttonPaletteInactivePressed.setBrush(QPalette::Background, QBrush(buttonImageInactivePressed));


	/* Start as an inactive button */

	this->setPalette(buttonPaletteInactive); 
	this->selected = false;


	/* Initialize the module name, font, and text palettes */

	moduleNameFont.setFamily("Segoe UI Semibold");
	moduleNameFont.setPixelSize(16);
	moduleNameFont.setStyleStrategy(QFont::PreferAntialias);

	moduleTextPaletteActive.setColor(QPalette::WindowText, QColor(31, 31, 31));
	moduleTextPaletteInactive.setColor(QPalette::WindowText, QColor(107, 107, 107));

	moduleNameLabel = new QLabel(TamperTypeName[tamperType]);
	moduleNameLabel->setContentsMargins(0, 10, 0, 0);
	moduleNameLabel->setAlignment(Qt::AlignHCenter);
	moduleNameLabel->setFont(moduleNameFont);
	moduleNameLabel->setPalette(moduleTextPaletteInactive);


	/* Add the Module Name to the layout */

	moduleLayout->addWidget(moduleNameLabel);

}

UiTamperModule* UiTamperModule::makeUiTamperModule(QWidget* parent, TamperType tamperType)
{
	switch (tamperType)
	{
		/* network condition */
		
		case SPEED:
			return new UiTamperSpeed(parent, tamperType);
		case DELAY:
			return new UiTamperDelay(parent, tamperType);
		case QUALITY:
			return new UiTamperQuality(parent, tamperType);

		/* network restrictions */

		case REDIR_TO_PORAL:
			return new UiTamperRedirToPortal(parent, tamperType);
		case CONTENT_BLOCKED:
			return new UiTamperContentBlocked(parent, tamperType);
		case HTTP_HTTPS_ONLY:
			return new UiTamperHTTPHTTPSOnly(parent, tamperType);

		/* network failures */

		case NO_INTERNET:
			return new UiTamperNoInternet(parent, tamperType);
		case NO_DNS:
			return new UiTamperNoDNS(parent, tamperType);
		case NO_SERVER:
			return new UiTamperNoServer(parent, tamperType);

		/* web service failures */

		case HTTP_TIME_OUT:
			return new UiTamperHTTPTimeOut(parent, tamperType);
		case HTTP_UNEXPECTED_RESPONSE:
			return new UiTamperHTTPUnexpectedResponse(parent, tamperType);
		case HTTP_CORRUPTED_RESPONSE:
			return new UiTamperHTTPCorruptedResponse(parent, tamperType);

		/* Should never reach these */

		case NUM_TAMPER_TYPES:
		default:
			__debugbreak();
			return nullptr;
	}
}

void UiTamperModule::select()
{
	this->setPalette(buttonPaletteActive);
	this->moduleNameLabel->setPalette(moduleTextPaletteActive);
	this->selected = true;
}


void UiTamperModule::unselect()
{
	this->setPalette(buttonPaletteInactive);
	this->moduleNameLabel->setPalette(moduleTextPaletteInactive);
	this->selected = false;
}


void UiTamperModule::mouseReleaseEvent(QMouseEvent *e)
{
	if (this->palette().background() == buttonPaletteActivePressed.background())
	{
		this->setPalette(buttonPaletteActive);
	}
	else if (this->palette().background() == buttonPaletteInactivePressed.background())
	{
		this->setPalette(buttonPaletteInactive);
	}

	emit tamperButtonClicked(this, pTamperConfig);
}

void UiTamperModule::mousePressEvent(QMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
	{
		if (this->palette().background() == buttonPaletteActive.background() || this->palette().background() == buttonPaletteActiveHover.background())
		{
			this->setPalette(buttonPaletteActivePressed);
		}
		else if (this->palette().background() == buttonPaletteInactive.background() || this->palette().background() == buttonPaletteInactiveHover.background())
		{
			this->setPalette(buttonPaletteInactivePressed);
		}
	}
}


void UiTamperModule::enterEvent(QEvent *e)
{
	if (this->palette().background() == buttonPaletteActive.background())
	{
		this->setPalette(buttonPaletteActiveHover);
	}
	else if (this->palette().background() == buttonPaletteInactive.background())
	{
		this->setPalette(buttonPaletteInactiveHover);
	}
}


void UiTamperModule::leaveEvent(QEvent *e)
{
	if (this->palette().background() == buttonPaletteActiveHover.background() || this->palette().background() == buttonPaletteActivePressed.background())
	{
		this->setPalette(buttonPaletteActive);
	}
	else if (this->palette().background() == buttonPaletteInactiveHover.background() || this->palette().background() == buttonPaletteInactivePressed.background())
	{
		this->setPalette(buttonPaletteInactive);
	}
}