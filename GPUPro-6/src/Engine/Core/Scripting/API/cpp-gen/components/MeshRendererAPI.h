#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace MeshRendererAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		int Get_MeshIndex(InstanceID managedInstanceId);
		void Set_MeshIndex(InstanceID managedInstanceId, int val);

		int Get_MaterialIndex(InstanceID managedInstanceId);
		void Set_MaterialIndex(InstanceID managedInstanceId, int val);
// ## Generated Code ##
	};
};