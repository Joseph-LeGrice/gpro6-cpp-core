#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace TypedObjectManagerAPI
	{
		extern void RegisterCalls();
		extern MonoObject* Create(MonoString* arg0);
	};
};