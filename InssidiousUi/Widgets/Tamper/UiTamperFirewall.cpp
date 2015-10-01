#include "UiTamperFirewall.h"
#include "Dialog/ConfigureFirewallDialog.h"

#include "Winsock2.h"
#pragma comment(lib, "ntdll.lib")

UiTamperFirewall::UiTamperFirewall(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = static_cast<void*>(new TamperFirewallConfig{ FIREWALL_OFF, static_cast<PSLIST_HEADER>(_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT)) });

	InitializeSListHead(static_cast<TamperFirewallConfig*>(pTamperConfig)->customPortList);
	dialogPortList.clear();
	portListVersion = 0;

	buttonGroup = new QButtonGroup();
	buttonLeft = new QPushButton();
	buttonMiddle1 = new QPushButton();
	buttonMiddle2 = new QPushButton();
	buttonRight = new QPushButton();

	buttonLeft->setStyleSheet(buttonLeftStyleSheet88);
	buttonMiddle1->setStyleSheet(buttonMiddleStyleSheet88);
	buttonMiddle2->setStyleSheet(buttonMiddleStyleSheet88);
	buttonRight->setStyleSheet(buttonRightStyleSheet88);

	buttonLeft->setText("Block Email");
	buttonMiddle1->setText("Block UDP");
	buttonMiddle2->setText("Block VPN");
	buttonRight->setText("Custom Rules");

	buttonLeft->setFixedSize(88, 30);
	buttonMiddle1->setFixedSize(88, 30);
	buttonMiddle2->setFixedSize(88, 30);
	buttonRight->setFixedSize(88, 30);

	buttonLeft->setCheckable(true);
	buttonMiddle1->setCheckable(true);
	buttonMiddle2->setCheckable(true);
	buttonRight->setCheckable(true);

	buttonLeft->setDisabled(true);
	buttonMiddle1->setDisabled(true);
	buttonMiddle2->setDisabled(true);
	buttonRight->setDisabled(true);

	buttonLeft->setAttribute(Qt::WA_TransparentForMouseEvents);
	buttonMiddle1->setAttribute(Qt::WA_TransparentForMouseEvents);
	buttonMiddle2->setAttribute(Qt::WA_TransparentForMouseEvents);
	buttonRight->setAttribute(Qt::WA_TransparentForMouseEvents);

	buttonGroup->setExclusive(true);
	buttonGroup->addButton(buttonLeft, 0);
	buttonGroup->addButton(buttonMiddle1, 1);
	buttonGroup->addButton(buttonMiddle2, 2);
	buttonGroup->addButton(buttonRight, 3);



	firewallLayout = new QGridLayout();
	firewallLayout->setSpacing(0);
	firewallLayout->setMargin(0);
	firewallLayout->setAlignment(Qt::AlignHCenter);
	firewallLayout->addWidget(buttonLeft, 0, 0);
	firewallLayout->addWidget(buttonMiddle1, 0, 1);
	firewallLayout->addWidget(buttonMiddle2, 0, 2);
	firewallLayout->addWidget(buttonRight, 0, 3);

	connect(buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &UiTamperFirewall::onButtonClicked);

	moduleLayout->addLayout(firewallLayout);
}


void UiTamperFirewall::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);


		/* Enable the buttons */

		buttonLeft->setEnabled(true);
		buttonMiddle1->setEnabled(true);
		buttonMiddle2->setEnabled(true);
		buttonRight->setEnabled(true);

		buttonLeft->setAttribute(Qt::WA_TransparentForMouseEvents, false);
		buttonMiddle1->setAttribute(Qt::WA_TransparentForMouseEvents, false);
		buttonMiddle2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
		buttonRight->setAttribute(Qt::WA_TransparentForMouseEvents, false);


		/* Set Block Email to Checked */

		if (buttonGroup->checkedId() == -1)
		{
			buttonLeft->setChecked(true);
			onButtonClicked(0);
		}


		/* Notify Core */

		emit tamperStart(this, pTamperConfig);
	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);


		/* Uncheck and disable all buttons */

		buttonGroup->setExclusive(false);

		buttonLeft->setChecked(false);
		buttonMiddle1->setChecked(false);
		buttonMiddle2->setChecked(false);
		buttonRight->setChecked(false);

		buttonLeft->setDisabled(true);
		buttonMiddle1->setDisabled(true);
		buttonMiddle2->setDisabled(true);
		buttonRight->setDisabled(true);

		buttonGroup->setExclusive(true);

		buttonLeft->setAttribute(Qt::WA_TransparentForMouseEvents);
		buttonMiddle1->setAttribute(Qt::WA_TransparentForMouseEvents);
		buttonMiddle2->setAttribute(Qt::WA_TransparentForMouseEvents);
		buttonRight->setAttribute(Qt::WA_TransparentForMouseEvents);

		/* Clear the button settings */

		onButtonClicked(-1);


		/* Notify core to stop */

		emit tamperStop(this);
	}
}


void UiTamperFirewall::onButtonClicked(int index)
{
	switch (buttonGroup->checkedId())
	{
	case -1 /* No Button Checked */:
		static_cast<TamperFirewallConfig*>(pTamperConfig)->firewallType = FIREWALL_OFF;
		break;
	case 0 /* Block Email */:
		static_cast<TamperFirewallConfig*>(pTamperConfig)->firewallType = FIREWALL_EMAIL;
		break;
	case 1 /* Block UDP */:
		static_cast<TamperFirewallConfig*>(pTamperConfig)->firewallType = FIREWALL_UDP;
		break;
	case 2 /* Block VPN */:
		static_cast<TamperFirewallConfig*>(pTamperConfig)->firewallType = FIREWALL_VPN;
		break;
	case 3 /* Custom Rules */:
	{
		/* Throw up the Custom Ports dialog */

		ConfigureFirewallDialog* dialog = new ConfigureFirewallDialog(this->parentWidget(), &dialogPortList);
		if (dialog->exec() == QDialog::Accepted)
		{
			/* The User clicked Save. Process the new port list */

			/* Create a new SList */
			
			PSLIST_HEADER newListHead = static_cast<PSLIST_HEADER>(_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT));
			InitializeSListHead(newListHead);
			portListVersion++;


			/* Add the new ports to the list */

			PSLIST_ENTRY entryLast = nullptr;
			PSLIST_ENTRY entryFirst = nullptr;
			for (unsigned short port : dialogPortList)
			{
				/* Allocate memory for the list entry */
				
				TamperFirewallEntry* pTamperFirewallEntry = static_cast<TamperFirewallEntry*>(_aligned_malloc(sizeof(TamperFirewallEntry), MEMORY_ALLOCATION_ALIGNMENT));

				/* Save the version and port number */

				pTamperFirewallEntry->version = portListVersion;
				pTamperFirewallEntry->portNumber = htons(port);


				/* Add the entry to the list */

				InterlockedPushEntrySList(newListHead, &(pTamperFirewallEntry->ItemEntry));
				
				if (entryLast == nullptr)
				{
					entryLast = &(pTamperFirewallEntry->ItemEntry);
				}
			}
			

			/* If we have valid first and last entries, push in the new list */

			entryFirst = RtlFirstEntrySList(newListHead);
			if (entryFirst && entryLast)
			{
				/* Clear any existing items in the port list */

				PSLIST_ENTRY staleItems = InterlockedFlushSList(static_cast<TamperFirewallConfig*>(pTamperConfig)->customPortList);
				

				/* Push the new list and set the type to FIREWALL_CUSTOM */

				InterlockedPushListSList(static_cast<TamperFirewallConfig*>(pTamperConfig)->customPortList, entryFirst, entryLast, dialogPortList.count());
				static_cast<TamperFirewallConfig*>(pTamperConfig)->firewallType = FIREWALL_CUSTOM;


				/* Free memory left over from any old existing items */

				while (staleItems != nullptr)
				{
					PSLIST_ENTRY tmp = staleItems;
					staleItems = staleItems->Next;
					_aligned_free(tmp);
					break;
				}
			}
			else
			{
				/* Should not get here */
				static_cast<TamperFirewallConfig*>(pTamperConfig)->firewallType = FIREWALL_OFF;
				__debugbreak();
			}
		}
		else
		{
			/* The user clicked Close or Cancel. Turn off the tamper module */
			setActive(false);
		}

		delete dialog;
		break;
	}
	default:
		/* Should not get here */
		static_cast<TamperFirewallConfig*>(pTamperConfig)->firewallType = FIREWALL_OFF;
		__debugbreak();
		break;
	}

}

