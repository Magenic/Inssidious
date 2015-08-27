#include "TamperBase.h"
#include "TamperTypes.h"

//#include "TamperContentBlocked.h"
//#include "TamperDelay.h"
//#include "TamperHTTPCorruptedResponse.h"
//#include "TamperHTTPHTTPSOnly.h"
//#include "TamperHTTPTimeOut.h"
//#include "TamperHTTPUnexpectedResponse.h"
//#include "TamperNoDNS.h"
//#include "TamperNoInternet.h"
//#include "TamperNoServer.h"
//#include "TamperQuality.h"
//#include "TamperRedirToPortal.h"
//#include "TamperSpeed.h"



TamperModule* TamperModule::makeTamperModule(int tamperType)
{
	switch (tamperType)
	{
		/* network condition */

		case SPEED:
			return new TamperSpeed();
		case DELAY:
			return new TamperDelay();
		case QUALITY:
			return new TamperQuality();
	
			/* network restrictions */
	
		case REDIR_TO_PORAL:
			return new TamperRedirToPortal();
		case CONTENT_BLOCKED:
			return new TamperContentBlocked();
		case HTTP_HTTPS_ONLY:
			return new TamperHTTPHTTPSOnly();
	
			/* network failures */
	
		case NO_INTERNET:
			return new TamperNoInternet();
		case NO_DNS:
			return new TamperNoDNS();
		case NO_SERVER:
			return new TamperNoServer();
	
			/* web service failures */
	
		case HTTP_TIME_OUT:
			return new TamperHTTPTimeOut();
		case HTTP_UNEXPECTED_RESPONSE:
			return new TamperHTTPUnexpectedResponse();
		case HTTP_CORRUPTED_RESPONSE:
			return new TamperHTTPCorruptedResponse();
	
			/* Should never reach these */
	
		case NUM_TAMPER_TYPES:
		default:
			__debugbreak();
			return nullptr;
	}
}
