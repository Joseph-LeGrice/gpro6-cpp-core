#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace StructuredBufferAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern MonoObject* GetResourceView(InstanceID managedInstanceId);
// ## Generated Code ##
	};
};