#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace LoggingAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern void LogMessage(MonoString* arg0);
// ## Generated Code ##
	};
};