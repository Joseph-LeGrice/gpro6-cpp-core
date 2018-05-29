#pragma once

#include "Engine/Core/RTTI/RTTI.h"

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

		extern void SetShader(InstanceID managedInstanceId, MonoObject* arg0);

		extern void RegisterShaderResource(InstanceID managedInstanceId, MonoObject* arg0, int arg1);

		extern void AddTextureSampler(InstanceID managedInstanceId, MonoObject* arg0, int arg1);

		extern void InitProperties(InstanceID managedInstanceId, MonoArray* arg0);

		extern void SetInteger(InstanceID managedInstanceId, MonoString* arg0, int arg1);

		extern void SetBoolean(InstanceID managedInstanceId, MonoString* arg0, bool arg1);

		extern void SetFloat(InstanceID managedInstanceId, MonoString* arg0, float arg1);

		extern void SetFloat2(InstanceID managedInstanceId, MonoString* arg0, Vector2 arg1);

		extern void SetFloat3(InstanceID managedInstanceId, MonoString* arg0, Vector3 arg1);

		extern void SetFloat4(InstanceID managedInstanceId, MonoString* arg0, Vector4 arg1);

		extern void SetMatrix3x3(InstanceID managedInstanceId, MonoString* arg0, Matrix3x3 arg1);

		extern void SetMatrix4x4(InstanceID managedInstanceId, MonoString* arg0, Matrix4x4 arg1);

		extern void SetCullState_Internal(int arg0, int arg1);

		extern void SetFillMode_Internal(int arg0, int arg1);

		extern void SetColorBlending_Internal(int arg0, int arg1, int arg2, int arg3);

		extern void SetAlphaBlending_Internal(int arg0, int arg1, int arg2, int arg3);
// ## Generated Code ##
	};
};