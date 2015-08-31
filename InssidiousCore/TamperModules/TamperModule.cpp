#include "TamperModule.h"

#include "TamperSpeed.h"
#include "TamperConditions.h"
#include "TamperFirewall.h"

#include "TamperNoInternet.h"
#include "TamperNoServer.h"
#include "TamperNoWebService.h"

#include "TamperTypes.h"


TamperModule* TamperModule::makeTamperModule(int tamperType, void** ppTamperConfig)
{
	switch (tamperType)
	{
		/* network condition */

		case SPEED:
			return new TamperSpeed(ppTamperConfig);
		case CONDITIONS:
			return new TamperConditions(ppTamperConfig);
		case FIREWALL:
			return new TamperFirewall(ppTamperConfig);
	
		/* network failures */
	
		case NO_INTERNET:
			return new TamperNoInternet(ppTamperConfig);
		case NO_SERVER:
			return new TamperNoServer(ppTamperConfig);
		case NO_WEBSERVICE:
			return new TamperNoWebService(ppTamperConfig);

		/* web service failures */
	
		//case HTTP_TIME_OUT:
		//	return new TamperHTTPTimeOut(ppTamperConfig);
		//case HTTP_UNEXPECTED_RESPONSE:
		//	return new TamperHTTPUnexpectedResponse(ppTamperConfig);
		//case HTTP_CORRUPTED_RESPONSE:
		//	return new TamperHTTPCorruptedResponse(ppTamperConfig);
	
		/* Should never reach these */
	
		case NUM_TAMPER_TYPES:
		default:
			__debugbreak();
			return nullptr;
	}
}
