#include "TamperModule.h"

#include "TamperSpeed.h"
#include "TamperConditions.h"
#include "TamperFirewall.h"
#include "TamperSecurity.h"

#include "TamperNoInternet.h"
#include "TamperNoServer.h"
#include "TamperNoContent.h"
#include "TamperNoWebService.h"

#include "TamperTypes.h"
#include <ctime>


TamperModule* TamperModule::makeTamperModule(int tamperType, void** ppTamperConfig)
{
	/* Tamper modules use rand(), so this will ensure a unique-ish seed */

	srand(time(nullptr));

	switch (tamperType)
	{
		/* scenarios */

		case SPEED:
			return new TamperSpeed(ppTamperConfig);
		case CONDITIONS:
			return new TamperConditions(ppTamperConfig);
		case FIREWALL:
			return new TamperFirewall(ppTamperConfig);
		case SECURITY:
			return new TamperSecurity(ppTamperConfig);
	

		/* failures */
	
		case NO_INTERNET:
			return new TamperNoInternet(ppTamperConfig);
		case NO_SERVER:
			return new TamperNoServer(ppTamperConfig);
		case NO_CONTENT:
			return new TamperNoContent(ppTamperConfig);
		case NO_WEBSERVICE:
			return new TamperNoWebService(ppTamperConfig);

	
		/* Should never reach */
	
		case NUM_TAMPER_TYPES:
		default:
			__debugbreak();
			return nullptr;
	}
}
