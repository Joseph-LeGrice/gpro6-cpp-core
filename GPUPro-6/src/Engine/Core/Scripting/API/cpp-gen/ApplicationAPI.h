#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace ApplicationAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern MonoString* GetInstallLocation();
// ## Generated Code ##
	};
};