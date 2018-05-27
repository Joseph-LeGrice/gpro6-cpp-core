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

		MonoObject* Get_Mesh(InstanceID managedInstanceId);
		void Set_Mesh(InstanceID managedInstanceId, MonoObject* val);

		MonoObject* Get_Material(InstanceID managedInstanceId);
		void Set_Material(InstanceID managedInstanceId, MonoObject* val);
// ## Generated Code ##
	};
};