#include "stdafx.h"
#include "Logging.h"


void Logging::LogMessage(MonoString* message)
{
	const char* msg = mono_string_to_utf8(message);
	Log(msg);
	mono_free((void*)msg);
}

void Logging::RegisterMonoMethods()
{
	mono_add_internal_call("Logging::LogMessage", Logging::LogMessage);
}
