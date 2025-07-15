#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace TypedObjectManagerAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern MonoObject* Create(MonoString* arg0);

		extern MonoObject* GetInstance(MonoString* arg0, int arg1);
// ## Generated Code ##
	};
};