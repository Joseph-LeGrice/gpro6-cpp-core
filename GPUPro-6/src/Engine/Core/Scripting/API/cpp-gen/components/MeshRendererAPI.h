#pragma once

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

		int Get_MeshIndex(int managedInstanceId);
		void Set_MeshIndex(int managedInstanceId, int val);

		int Get_MaterialIndex(int managedInstanceId);
		void Set_MaterialIndex(int managedInstanceId, int val);
// ## Generated Code ##
	};
};