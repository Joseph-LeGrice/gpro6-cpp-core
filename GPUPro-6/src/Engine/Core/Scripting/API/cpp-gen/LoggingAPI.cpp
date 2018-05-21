#include "stdafx.h"
#include "LoggingAPI.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

// ## Generated Code ##
extern void GPro::LoggingAPI::RegisterCalls()
{
	mono_add_internal_call("Logging::LogMessage", GPro::LoggingAPI::LogMessage);
}


// ## Generated Code ##

void GPro::LoggingAPI::LogMessage(MonoString* arg0)
{
	const char* msg = mono_string_to_utf8(arg0);
	Log(msg);
	mono_free((void*)msg);
}
