#include "UiTamperFirewall.h"
#include <QtWidgets/QAbstractItemView>

class FComboBox : public QComboBox
{

public:

	/* Show pop up on all mouseReleaseEvents received by QComboBox */

	void FComboBox::mouseReleaseEvent(QMouseEvent *event)
	{
		FComboBox::showPopup();
	}

};

UiTamperFirewall::UiTamperFirewall(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperFirewallConfig{ true, true, false };

	firewallDescriptionLabel = new QLabel();
	firewallDescriptionLabel->setText(firewallDescriptionText);
	firewallDescriptionLabel->setFixedHeight(12);
	firewallDescriptionLabel->setAlignment(Qt::AlignHCenter);
	firewallDescriptionLabel->setFont(moduleDescriptionFont);
	firewallDescriptionLabel->setPalette(moduleTextPaletteInactive);


	httpDescriptionLabel = new QLabel();
	httpDescriptionLabel->setText(httpDescriptionText);
	httpDescriptionLabel->setFixedHeight(30);
	httpDescriptionLabel->setWordWrap(true);
	httpDescriptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	httpDescriptionLabel->setFont(moduleDescriptionFont);
	httpDescriptionLabel->setPalette(moduleTextPaletteInactive);

	httpComboBox = new FComboBox();
	httpComboBox->setFixedSize(106, 24);
	httpComboBox->setEditable(true);
	httpComboBox->lineEdit()->setReadOnly(true);
	httpComboBox->lineEdit()->setFont(moduleDescriptionFont);
	httpComboBox->view()->setFont(moduleDescriptionFont);
	lineEditPaletteInactive = QPalette(moduleTextPaletteInactive);
	lineEditPaletteActive = QPalette(moduleTextPaletteActive);
	lineEditPaletteInactive.setColor(QPalette::Inactive, QPalette::Base, QColor(240, 240, 240));
	lineEditPaletteActive.setColor(QPalette::Active, QPalette::Base, QColor(114, 197, 93));
	lineEditPaletteActive.setColor(QPalette::Inactive, QPalette::Base, QColor(114, 197, 93));
	httpComboBox->lineEdit()->setPalette(moduleTextPaletteInactive);
	httpComboBox->setStyleSheet("QComboBox:disabled { border: 1px solid #ABABAB; border-radius: 2px; background-color: #F0F0F0; color: gray; } QComboBox {	border: 1px solid #72C55D; border-radius: 2px; background-color: #FDFDFD; color:#444444; font-family: 'Segoe UI Semibold'; font-size:11px; font-weight:400; text-decoration:none;}QComboBox:hover {    border: 2px solid #72C55D;}QComboBox:!editable:hover {    border: 2px solid #72C55D;}QComboBox:on {    background-color: #72C55D; color:#333333;}QComboBox::down-arrow:disabled { width: 24px;    height: 24px;	image: url(:/InssidiousUi/DownArrowDisabled.png); } QComboBox::down-arrow {  width: 24px;    height: 24px;	image: url(:/InssidiousUi/DownArrow.png);}QComboBox::drop-down {    subcontrol-origin: margin;    subcontrol-position: top right;    width: 20px;    border-style: none;    border-image: none;}");
	


	httpComboBox->lineEdit()->setContentsMargins(0, 0, 0, 0);
	httpComboBox->lineEdit()->setAlignment(Qt::AlignCenter);					//Only possible when LineEdit is editable
	httpComboBox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);	//Allows QComboBox to still display dropdown on click
	httpComboBox->addItem("HTTP & HTTPS");
	httpComboBox->addItem("HTTPS Only");
	httpComboBox->addItem("HTTP Only");
	httpComboBox->setItemData(0, Qt::AlignCenter, Qt::TextAlignmentRole);
	httpComboBox->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);
	httpComboBox->setItemData(2, Qt::AlignCenter, Qt::TextAlignmentRole);
	httpComboBox->lineEdit()->setDisabled(true);
	httpComboBox->setDisabled(true);

	filterDescriptionLabel = new QLabel();
	filterDescriptionLabel->setText(filterDescriptionText);
	filterDescriptionLabel->setFixedHeight(30);
	filterDescriptionLabel->setWordWrap(true);
	filterDescriptionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	filterDescriptionLabel->setFont(moduleDescriptionFont);
	filterDescriptionLabel->setPalette(moduleTextPaletteInactive);

	filterButton = new QPushButton();
	filterButton->setStyleSheet(buttonStyleSheet);
	filterButton->setText("Block All Content");
	filterButton->setFont(moduleDescriptionFont);
	filterButton->setFixedSize(106, 24);
	filterButton->setCheckable(true);
	filterButton->setDisabled(true);



	firewallLayout = new QGridLayout();
	firewallLayout->setAlignment(Qt::AlignHCenter);
	firewallLayout->setSpacing(0);
	firewallLayout->addItem(new QSpacerItem(0, 6), 0, 0);
	firewallLayout->addWidget(firewallDescriptionLabel, 1, 0, 1, 3);
	firewallLayout->addItem(new QSpacerItem(0, 12), 2, 0);
	firewallLayout->addWidget(httpDescriptionLabel, 3, 0);
	firewallLayout->addWidget(httpComboBox, 3, 1, 1, 2, Qt::AlignCenter);
	firewallLayout->addItem(new QSpacerItem(0, 2), 4, 0);
	firewallLayout->addWidget(filterDescriptionLabel, 5, 0);
	firewallLayout->addWidget(filterButton, 5, 1, 1, 2, Qt::AlignCenter);


	connect(httpComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &UiTamperFirewall::onHTTPComboBoxChanged);
	connect(filterButton, &QPushButton::clicked, this, &UiTamperFirewall::onFilterButtonClicked);


	moduleLayout->addLayout(firewallLayout);
}

UiTamperFirewall::~UiTamperFirewall()
{

}

void UiTamperFirewall::toggleState(bool active)
{
	if (active)
	{
		firewallDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		httpDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		filterDescriptionLabel->setPalette(this->moduleTextPaletteActive);
		httpComboBox->lineEdit()->setPalette(this->lineEditPaletteActive);
		httpComboBox->setEnabled(true);
		httpComboBox->lineEdit()->setEnabled(true);
		filterButton->setEnabled(true);
	}
	else
	{
		firewallDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		httpDescriptionLabel->setPalette(this->moduleTextPaletteInactive);
		httpComboBox->lineEdit()->setPalette(this->lineEditPaletteInactive);
		filterDescriptionLabel->setPalette(this->moduleTextPaletteInactive);

		if (filterButton->isChecked())
		{
			filterButton->setChecked(false);
			filterButton->clicked();
		}

		httpComboBox->lineEdit()->setDisabled(true);
		httpComboBox->setDisabled(true);
		filterButton->setDisabled(true);
	}
}


void UiTamperFirewall::onHTTPComboBoxChanged(int index)
{
	switch (index)
	{
	case 0:
		((TamperFirewallConfig*)pTamperConfig)->allowHTTP = true;
		((TamperFirewallConfig*)pTamperConfig)->allowHTTPS = true;
		break;

	case 1:
		((TamperFirewallConfig*)pTamperConfig)->allowHTTP = false;
		((TamperFirewallConfig*)pTamperConfig)->allowHTTPS = true;
		break;

	case 2:
		((TamperFirewallConfig*)pTamperConfig)->allowHTTP = true;
		((TamperFirewallConfig*)pTamperConfig)->allowHTTPS = false;
		break;
	}
}

void UiTamperFirewall::onFilterButtonClicked()
{
	if (filterButton->isChecked())
	{
		((TamperFirewallConfig*)pTamperConfig)->contentBlocked = true;
	}
	else
	{
		((TamperFirewallConfig*)pTamperConfig)->contentBlocked = false;
	}
}

