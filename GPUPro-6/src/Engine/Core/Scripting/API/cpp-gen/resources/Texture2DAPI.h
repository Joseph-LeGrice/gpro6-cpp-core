#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace Texture2DAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern void InitializeWithBitmap(InstanceID managedInstanceId, MonoString* arg0);

		extern MonoObject* GetResource(InstanceID managedInstanceId);
// ## Generated Code ##
	};
};