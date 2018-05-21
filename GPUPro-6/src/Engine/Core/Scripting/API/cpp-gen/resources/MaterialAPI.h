#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace MaterialAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern void SetShaderIndex(int managedInstanceId, int arg0);

		extern void RegisterShaderResource(int managedInstanceId, int arg0, int arg1);

		extern void AddTextureSampler(int managedInstanceId, int arg0, int arg1);

		extern void SetInteger(int managedInstanceId, MonoString* arg0, int arg1);

		extern void SetBoolean(int managedInstanceId, MonoString* arg0, bool arg1);

		extern void SetFloat(int managedInstanceId, MonoString* arg0, float arg1);

		extern void SetFloat2(int managedInstanceId, MonoString* arg0, Vector2 arg1);

		extern void SetFloat3(int managedInstanceId, MonoString* arg0, Vector3 arg1);

		extern void SetFloat4(int managedInstanceId, MonoString* arg0, Vector4 arg1);

		extern void SetMatrix3x3(int managedInstanceId, MonoString* arg0, Matrix3x3 arg1);

		extern void SetMatrix4x4(int managedInstanceId, MonoString* arg0, Matrix4x4 arg1);
// ## Generated Code ##
	};
};