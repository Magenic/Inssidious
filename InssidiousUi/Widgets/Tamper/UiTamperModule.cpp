#include "UiTamperModule.h"

#include "UiTamperSpeed.h"
#include "UiTamperConditions.h"
#include "UiTamperFirewall.h"

#include "UiTamperNoWebService.h"
#include "UiTamperNoInternet.h"
#include "UiTamperNoServer.h"

//#include "UiTamperHTTPCorruptedResponse.h"
//#include "UiTamperHTTPTimeOut.h"
//#include "UiTamperHTTPUnexpectedResponse.h"



UiTamperModule::UiTamperModule(QWidget* parent, TamperType tamperType)
	: QWidget(parent)
{

	/* Set the layout and initial settings */

	moduleLayout = new QVBoxLayout();
	moduleLayout->setMargin(0);
	moduleLayout->setSpacing(0);
	moduleLayout->setAlignment(Qt::AlignTop);
	
	this->setLayout(moduleLayout);
	this->setFixedWidth(232);
	this->setFixedHeight(130);
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

	moduleTextPaletteActive.setColor(QPalette::WindowText, QColor(255, 255, 255));
	moduleTextPaletteActive.setColor(QPalette::ButtonText, QColor(0, 0, 0));
	moduleTextPaletteInactive.setColor(QPalette::WindowText, QColor(83, 84, 85));

	moduleNameFont.setFamily("Segoe UI");
	moduleNameFont.setWeight(QFont::DemiBold);
	moduleNameFont.setPixelSize(15);
	moduleNameFont.setStyleStrategy(QFont::PreferAntialias);

	moduleNameLabel = new QLabel(TamperTypeName[tamperType]);
	moduleNameLabel->setContentsMargins(0, 10, 0, 0);
	moduleNameLabel->setAlignment(Qt::AlignHCenter);
	moduleNameLabel->setFont(moduleNameFont);
	moduleNameLabel->setPalette(moduleTextPaletteInactive);

	moduleDescriptionFont.setFamily("Segoe UI Semibold");
	moduleDescriptionFont.setPixelSize(11);
	moduleDescriptionFont.setWeight(QFont::DemiBold);
	moduleDescriptionFont.setStyleStrategy(QFont::PreferAntialias);


	lineEditPaletteInactive = QPalette(moduleTextPaletteInactive);
	lineEditPaletteActive = QPalette(moduleTextPaletteActive);
	lineEditPaletteInactive.setColor(QPalette::Inactive, QPalette::Base, QColor(240, 240, 240));
	lineEditPaletteActive.setColor(QPalette::Active, QPalette::Base, QColor(114, 197, 93));
	lineEditPaletteActive.setColor(QPalette::Inactive, QPalette::Base, QColor(114, 197, 93));



	/* Add the Module Name & Description to the layout */

	moduleLayout->addWidget(moduleNameLabel);


}

UiTamperModule* UiTamperModule::makeUiTamperModule(QWidget* parent, TamperType tamperType)
{
	switch (tamperType)
	{
		/* network condition */
		
		case SPEED:
			return new UiTamperSpeed(parent, tamperType);
		case CONDITIONS:
			return new UiTamperConditions(parent, tamperType);
		case FIREWALL:
			return new UiTamperFirewall(parent, tamperType);

		/* network failures */

		case NO_INTERNET:
			return new UiTamperNoInternet(parent, tamperType);
		case NO_SERVER:
			return new UiTamperNoServer(parent, tamperType);
		case NO_WEBSERVICE:
			return new UiTamperNoWebService(parent, tamperType);

		/* web service failures */

		//case HTTP_TIME_OUT:
		//	return new UiTamperHTTPTimeOut(parent, tamperType);
		//case HTTP_UNEXPECTED_RESPONSE:
		//	return new UiTamperHTTPUnexpectedResponse(parent, tamperType);
		//case HTTP_CORRUPTED_RESPONSE:
		//	return new UiTamperHTTPCorruptedResponse(parent, tamperType);

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
	this->toggleState(true);
	this->selected = true;
}


void UiTamperModule::unselect()
{
	this->setPalette(buttonPaletteInactive);
	this->moduleNameLabel->setPalette(moduleTextPaletteInactive);
	this->toggleState(false);
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