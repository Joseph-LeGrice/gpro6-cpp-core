#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace EntityAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern MonoObject* AddComponentInternal(int arg0, MonoString* arg1);

		extern void RemoveComponentInternal(int arg0, MonoString* arg1);

		extern MonoObject* GetComponentInternal(int arg0, MonoString* arg1);
// ## Generated Code ##
	};
};