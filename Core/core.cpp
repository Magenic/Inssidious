#include "core.h"

Core::Core()
{

}

Core::~Core()
{

}

void Core::start()
{
	//Do initialization work

	if (true)
	{
		//Emit coreStarted 
		emit coreStarted();
	}
	else
	{
		emit coreStartFailed("Error message");
	}
}