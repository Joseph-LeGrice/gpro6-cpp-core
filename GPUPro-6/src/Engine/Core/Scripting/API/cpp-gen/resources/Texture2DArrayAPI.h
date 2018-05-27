#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace Texture2DArrayAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern void InitializeWithBitmaps(InstanceID managedInstanceId, MonoArray* arg0);

		extern int GetResourceViewID(InstanceID managedInstanceId);
// ## Generated Code ##
	};
};