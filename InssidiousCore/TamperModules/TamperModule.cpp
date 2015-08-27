#include "TamperModule.h"

#include "TamperContentBlocked.h"
#include "TamperDelay.h"
#include "TamperHTTPCorruptedResponse.h"
#include "TamperHTTPHTTPSOnly.h"
#include "TamperHTTPTimeOut.h"
#include "TamperHTTPUnexpectedResponse.h"
#include "TamperNoDNS.h"
#include "TamperNoInternet.h"
#include "TamperNoServer.h"
#include "TamperQuality.h"
#include "TamperRedirToPortal.h"
#include "TamperSpeed.h"

#include "TamperTypes.h"


TamperModule* TamperModule::makeTamperModule(int tamperType, void** ppTamperConfig)
{
	switch (tamperType)
	{
		/* network condition */

		case SPEED:
			return new TamperSpeed(ppTamperConfig);
		case DELAY:
			return new TamperDelay(ppTamperConfig);
		case QUALITY:
			return new TamperQuality(ppTamperConfig);
	
		/* network restrictions */
	
		case REDIR_TO_PORAL:
			return new TamperRedirToPortal(ppTamperConfig);
		case CONTENT_BLOCKED:
			return new TamperContentBlocked(ppTamperConfig);
		case HTTP_HTTPS_ONLY:
			return new TamperHTTPHTTPSOnly(ppTamperConfig);
	
		/* network failures */
	
		case NO_INTERNET:
			return new TamperNoInternet(ppTamperConfig);
		case NO_DNS:
			return new TamperNoDNS(ppTamperConfig);
		case NO_SERVER:
			return new TamperNoServer(ppTamperConfig);
	
		/* web service failures */
	
		case HTTP_TIME_OUT:
			return new TamperHTTPTimeOut(ppTamperConfig);
		case HTTP_UNEXPECTED_RESPONSE:
			return new TamperHTTPUnexpectedResponse(ppTamperConfig);
		case HTTP_CORRUPTED_RESPONSE:
			return new TamperHTTPCorruptedResponse(ppTamperConfig);
	
		/* Should never reach these */
	
		case NUM_TAMPER_TYPES:
		default:
			__debugbreak();
			return nullptr;
	}
}
