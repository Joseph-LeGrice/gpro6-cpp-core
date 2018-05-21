#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace TransformAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		Vector3 Get_position(int managedInstanceId);
		void Set_position(int managedInstanceId, Vector3 val);

		Vector3 Get_scale(int managedInstanceId);
		void Set_scale(int managedInstanceId, Vector3 val);

		Quaternion Get_rotation(int managedInstanceId);
		void Set_rotation(int managedInstanceId, Quaternion val);
// ## Generated Code ##
	};
};