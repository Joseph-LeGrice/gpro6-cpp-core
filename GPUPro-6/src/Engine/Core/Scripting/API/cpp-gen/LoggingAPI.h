#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace LoggingAPI
	{
		extern void RegisterCalls();
		extern void LogMessage(MonoString* arg0);
	};
};