#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace LightAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		float Get_Range(InstanceID managedInstanceId);
		void Set_Range(InstanceID managedInstanceId, float val);
// ## Generated Code ##
	};
};