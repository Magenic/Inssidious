#include "core.h"

Core::Core()
{
	//initialize some pointers from core.h
	//no heavy lifting here
}

Core::~Core()
{

}

void Core::onThreadStart()
{
	//Do actual initialization work

	if (true)
	{
		emit coreStarted();
	}
	else
	{
		emit coreStartFailed("Error message");
	}
}

void Core::onInssidiousStart()
{

	if (true)
	{
		emit inssidiousStarted();
	}
	else
	{
		emit inssidiousStartFailed("Error message");
	}
}