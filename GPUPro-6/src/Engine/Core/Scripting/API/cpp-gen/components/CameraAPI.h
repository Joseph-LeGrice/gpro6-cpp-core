#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace CameraAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern void SetOrthographic(InstanceID managedInstanceId, float arg0, float arg1, float arg2);

		extern void SetPerspective(InstanceID managedInstanceId, float arg0, float arg1, float arg2, float arg3);
// ## Generated Code ##
	};
};