#include "UiTamperNoServer.h"

#include "Dialog\ConfigureServersDialog.h"

#include <WS2tcpip.h>


UiTamperNoServer::UiTamperNoServer(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = static_cast<void*>(new TamperNoServerConfig{ NO_SERVERS_OFF, static_cast<PSLIST_HEADER>(_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT)) });

	InitializeSListHead(static_cast<TamperNoServerConfig*>(pTamperConfig)->noServersList);
	dialogServerList.clear();
	serverListVersion = 0;


	noServerLayout = new QGridLayout();
	noServerLayout->setSpacing(0);
	noServerLayout->setAlignment(Qt::AlignHCenter);


	buttonImagePaletteActive.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/TamperNoServerActive.png")));
	buttonImagePaletteInactive.setBrush(QPalette::Background, QBrush(QPixmap(":/Tamper/TamperNoServerInactive.png")));

	buttonImage = new QLabel(this);
	buttonImage->setPalette(buttonImagePaletteInactive);
	buttonImage->setAutoFillBackground(true);
	buttonImage->setGeometry(0, 0, 380, 120);
	buttonImage->setAttribute(Qt::WA_TransparentForMouseEvents);
	buttonImage->show();

	moduleLayout->addLayout(noServerLayout);
}


void UiTamperNoServer::setActive(bool active)
{
	if (active)
	{
		/* Show the module as active */

		this->setPalette(moduleBackgroundPaletteActive);
		this->buttonImage->setPalette(buttonImagePaletteActive);
		

		ConfigureServersDialog* dialog = new ConfigureServersDialog(this->parentWidget(), &dialogServerList);
		if (dialog->exec() == QDialog::Accepted)
		{
			/* The User clicked Save. Process the new port list */

			/* Create a new SList */

			PSLIST_HEADER newListHead = static_cast<PSLIST_HEADER>(_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT));
			InitializeSListHead(newListHead);
			serverListVersion++;


			/* Add the new ports to the list */

			PSLIST_ENTRY entryLast = nullptr;
			PSLIST_ENTRY entryFirst = nullptr;
			for (auto server : dialogServerList)
			{

				/* Allocate memory for the list entry */

				TamperNoServerEntry* pNoServerEntry = static_cast<TamperNoServerEntry*>(_aligned_malloc(sizeof(TamperNoServerEntry), MEMORY_ALLOCATION_ALIGNMENT));

				/* Save the version and port number */

				pNoServerEntry->version = serverListVersion;
				pNoServerEntry->server = inet_addr(server.split(" - ").first().toLocal8Bit());
				

				/* Add the entry to the list */

				InterlockedPushEntrySList(newListHead, &(pNoServerEntry->ItemEntry));

				if (entryLast == nullptr)
				{
					entryLast = &(pNoServerEntry->ItemEntry);
				}
			}


			/* If we have valid first and last entries, push in the new list */

			entryFirst = RtlFirstEntrySList(newListHead);
			if (entryFirst && entryLast)
			{
				/* Clear any existing items in the port list */

				PSLIST_ENTRY staleItems = InterlockedFlushSList(static_cast<TamperNoServerConfig*>(pTamperConfig)->noServersList);


				/* Push the new list and set the type to FIREWALL_CUSTOM */

				InterlockedPushListSList(static_cast<TamperNoServerConfig*>(pTamperConfig)->noServersList, entryFirst, entryLast, dialogServerList.count());
				static_cast<TamperNoServerConfig*>(pTamperConfig)->noServersType = NO_SERVERS_CUSTOM;


				/* Notify Core */

				emit tamperStart(this, pTamperConfig);


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
				static_cast<TamperNoServerConfig*>(pTamperConfig)->noServersType = NO_SERVERS_OFF;
				__debugbreak();
			}
		}
		else
		{
			/* The user clicked Close or Cancel. Turn off the tamper module */
			setActive(false);
		}

		delete dialog;

	}
	else
	{
		/* Show the module as inactive */

		this->setPalette(moduleBackgroundPaletteInactive);
		this->buttonImage->setPalette(buttonImagePaletteInactive);


		/* Set the config value to false */

		static_cast<TamperNoServerConfig*>(pTamperConfig)->noServersType = NO_SERVERS_OFF;


		/* Notify Core */

		emit tamperStop(this);
	}
}
