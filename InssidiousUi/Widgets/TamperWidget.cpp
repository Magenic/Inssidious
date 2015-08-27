#include "TamperWidget.h"

TamperWidget::TamperWidget(QWidget *parent)
	: QWidget(parent)
{
	/* Initialize the Tamper Widget Container */

	this->setAutoFillBackground(true);
	twContainerPalette.setBrush(QPalette::Background,		//Set a background image for the devices present palette
		QBrush(tcBackgroundImageDevicesPresent));				//With the tab container area background image
	this->setPalette(twContainerPalette);
	this->setGeometry(10 /* in */, 108 /* down */, 780 /* width */, 480 /* height */);

	twContainerVLayout = new QVBoxLayout();
	this->setLayout(twContainerVLayout);
	this->twContainerVLayout->setContentsMargins(0, 0, 0, 0);
	this->twContainerVLayout->setSpacing(0);




	tamperClassFont.setPixelSize(16);
	tamperClassFont.setFamily("Segoe UI Semibold");
	tamperClassFont.setStyleStrategy(QFont::PreferAntialias);


	for (int i = 0; i < NUM_TAMPER_CLASSES; i++)
	{
		tamperClassLabel[i] = new QLabel(TamperClassName[i]);
		tamperClassLabel[i]->setFixedHeight(22);
		tamperClassLabel[i]->setFont(tamperClassFont);
		tamperClassLabel[i]->setStyleSheet(QString("QLabel { color : #46514B; }"));
		tamperClassLabel[i]->setAlignment(Qt::AlignCenter);
		this->twContainerVLayout->addWidget(this->tamperClassLabel[i], Qt::AlignHCenter);


		tamperClassLayout[i] = new QHBoxLayout();
		this->twContainerVLayout->addLayout(this->tamperClassLayout[i], Qt::AlignHCenter);
	}



	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		tamperModule[i] = UiTamperModule::makeUiTamperModule(this, TamperType(i));
		tamperModule[i]->setParent(this);
		connect(this->tamperModule[i], &UiTamperModule::tamperButtonClicked, this, &TamperWidget::onTamperModuleClicked);
	}



	/* Add the Tamper Types to the appropriate class layouts */

	this->tamperClassLayout[CONDITIONS]->addWidget(this->tamperModule[SPEED]);
	this->tamperClassLayout[CONDITIONS]->addWidget(this->tamperModule[DELAY]);
	this->tamperClassLayout[CONDITIONS]->addWidget(this->tamperModule[QUALITY]);

	this->tamperClassLayout[RESTRICTIONS]->addWidget(this->tamperModule[REDIR_TO_PORAL]);
	this->tamperClassLayout[RESTRICTIONS]->addWidget(this->tamperModule[CONTENT_BLOCKED]);
	this->tamperClassLayout[RESTRICTIONS]->addWidget(this->tamperModule[HTTP_HTTPS_ONLY]);

	this->tamperClassLayout[NETWORK_FAILURES]->addWidget(this->tamperModule[NO_INTERNET]);
	this->tamperClassLayout[NETWORK_FAILURES]->addWidget(this->tamperModule[NO_DNS]);
	this->tamperClassLayout[NETWORK_FAILURES]->addWidget(this->tamperModule[NO_SERVER]);

	this->tamperClassLayout[WEB_SERVICE_FAILURES]->addWidget(this->tamperModule[HTTP_TIME_OUT]);
	this->tamperClassLayout[WEB_SERVICE_FAILURES]->addWidget(this->tamperModule[HTTP_UNEXPECTED_RESPONSE]);
	this->tamperClassLayout[WEB_SERVICE_FAILURES]->addWidget(this->tamperModule[HTTP_CORRUPTED_RESPONSE]);

}

TamperWidget::~TamperWidget()
{

}

void TamperWidget::onTamperModuleClicked(UiTamperModule* signaled)
{
	for (int i = 0; i < NUM_TAMPER_TYPES; i++)
	{
		if (tamperModule[i] == signaled)
		{
			if (tamperModule[i]->selected)
			{
				emit tamperStop(this, TamperType(i));
				tamperModule[i]->unselect();
			}
			else
			{
				emit tamperStart(this, TamperType(i));
				tamperModule[i]->select();
			}
		}
	}
}