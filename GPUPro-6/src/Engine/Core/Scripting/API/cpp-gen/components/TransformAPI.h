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

		MonoObject* Get_position(int managedInstanceId);
		void Set_position(int managedInstanceId, MonoObject* val);

		MonoObject* Get_scale(int managedInstanceId);
		void Set_scale(int managedInstanceId, MonoObject* val);

		MonoObject* Get_rotation(int managedInstanceId);
		void Set_rotation(int managedInstanceId, MonoObject* val);
// ## Generated Code ##
	};
};