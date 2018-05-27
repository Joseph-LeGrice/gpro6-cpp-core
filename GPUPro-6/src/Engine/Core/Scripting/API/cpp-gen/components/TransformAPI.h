#pragma once

#include "Engine/Core/RTTI/RTTI.h"

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

		Vector3 Get_position(InstanceID managedInstanceId);
		void Set_position(InstanceID managedInstanceId, Vector3 val);

		Vector3 Get_scale(InstanceID managedInstanceId);
		void Set_scale(InstanceID managedInstanceId, Vector3 val);

		Quaternion Get_rotation(InstanceID managedInstanceId);
		void Set_rotation(InstanceID managedInstanceId, Quaternion val);
// ## Generated Code ##
	};
};