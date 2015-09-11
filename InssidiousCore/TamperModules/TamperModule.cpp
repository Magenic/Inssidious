#include "TamperModule.h"

#include "TamperSpeed.h"
#include "TamperConditions.h"
#include "TamperFirewall.h"
#include "TamperDamage.h"

#include "TamperNoInternet.h"
#include "TamperNoServer.h"
#include "TamperNoWebContent.h"
#include "TamperWebServiceFailures.h"

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
		case DAMAGE:
			return new TamperDamage(ppTamperConfig);
	

		/* failures */
	
		case NO_INTERNET:
			return new TamperNoInternet(ppTamperConfig);
		case NO_SERVER:
			return new TamperNoServer(ppTamperConfig);
		case NO_WEB_CONTENT:
			return new TamperNoWebContent(ppTamperConfig);
		case WEBSERVICE_FAILURES:
			return new TamperWebServiceFailures(ppTamperConfig);

	
		/* Should never reach */
	
		case NUM_TAMPER_TYPES:
		default:
			__debugbreak();
			return nullptr;
	}
}
