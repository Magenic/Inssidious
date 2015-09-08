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
	firewallDescriptionLabel->setFixedHeight(16);
	firewallDescriptionLabel->setAlignment(Qt::AlignHCenter);
	firewallDescriptionLabel->setFont(moduleTextFont);
	firewallDescriptionLabel->setPalette(moduleTextPalette);


	httpDescriptionLabel = new QLabel();
	httpDescriptionLabel->setText(httpDescriptionText);
	httpDescriptionLabel->setFixedHeight(24);
	httpDescriptionLabel->setWordWrap(true);
	httpDescriptionLabel->setAlignment(Qt::AlignCenter);
	httpDescriptionLabel->setFont(moduleTextFont);
	httpDescriptionLabel->setPalette(moduleTextPalette);

	httpComboBox = new FComboBox();
	httpComboBox->setFixedSize(130, 30);
	httpComboBox->setEditable(true);
	httpComboBox->lineEdit()->setReadOnly(true);
	httpComboBox->lineEdit()->setFont(moduleTextFont);
	httpComboBox->view()->setFont(moduleTextFont);
	httpComboBox->setStyleSheet(comboBoxStyleSheet);
	


	httpComboBox->lineEdit()->setContentsMargins(0, 0, 0, 0);
	httpComboBox->lineEdit()->setAlignment(Qt::AlignCenter);					//Only possible when LineEdit is editable
	httpComboBox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);	//Allows QComboBox to still display dropdown on click
	httpComboBox->addItem("HTTP & HTTPS");
	httpComboBox->addItem("HTTPS Only");
	httpComboBox->addItem("HTTP Only");
	httpComboBox->setItemData(0, Qt::AlignCenter, Qt::TextAlignmentRole);
	httpComboBox->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);
	httpComboBox->setItemData(2, Qt::AlignCenter, Qt::TextAlignmentRole);


	filterDescriptionLabel = new QLabel();
	filterDescriptionLabel->setText(filterDescriptionText);
	filterDescriptionLabel->setFixedHeight(24);
	filterDescriptionLabel->setWordWrap(true);
	filterDescriptionLabel->setAlignment(Qt::AlignCenter);
	filterDescriptionLabel->setFont(moduleTextFont);
	filterDescriptionLabel->setPalette(moduleTextPalette);

	filterButton = new QPushButton();
	filterButton->setStyleSheet(buttonStyleSheet);
	filterButton->setText("Block All Content");
	filterButton->setFont(moduleTextFont);
	filterButton->setFixedSize(130, 30);
	filterButton->setCheckable(true);



	firewallLayout = new QGridLayout();
	firewallLayout->setHorizontalSpacing(20);
	firewallLayout->setAlignment(Qt::AlignHCenter);
	firewallLayout->addItem(new QSpacerItem(0, 6), 0, 0);
	firewallLayout->addWidget(firewallDescriptionLabel, 1, 0, 1, 2);
	firewallLayout->addItem(new QSpacerItem(0, 6), 2, 0);
	firewallLayout->addWidget(httpDescriptionLabel, 3, 0);
	firewallLayout->addWidget(httpComboBox, 4, 0, Qt::AlignHCenter);
	firewallLayout->addWidget(filterDescriptionLabel, 3, 1);
	firewallLayout->addWidget(filterButton, 4, 1, Qt::AlignHCenter);


	connect(httpComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &UiTamperFirewall::onHTTPComboBoxChanged);
	connect(filterButton, &QPushButton::clicked, this, &UiTamperFirewall::onFilterButtonClicked);


	moduleLayout->addLayout(firewallLayout);
}

UiTamperFirewall::~UiTamperFirewall()
{

}

void UiTamperFirewall::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		httpComboBox->setEnabled(true);
		httpComboBox->lineEdit()->setEnabled(true);
		filterButton->setEnabled(true);


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);


		/* Uncheck and disable all buttons */

		if (filterButton->isChecked())
		{
			filterButton->setChecked(false);
			filterButton->clicked();
		}

		httpComboBox->lineEdit()->setDisabled(true);
		httpComboBox->setDisabled(true);
		filterButton->setDisabled(true);



		/* Notify core to stop */

		emit tamperStop(this);
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

