#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace ShaderAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern void InitVertexShader(InstanceID managedInstanceId, MonoString* arg0, MonoString* arg1);

		extern void InitPixelShader(InstanceID managedInstanceId, MonoString* arg0, MonoString* arg1);

		extern void InitGeometryShader(InstanceID managedInstanceId, MonoString* arg0, MonoString* arg1);

		extern void InitHullShader(InstanceID managedInstanceId, MonoString* arg0, MonoString* arg1);

		extern void InitDomainShader(InstanceID managedInstanceId, MonoString* arg0, MonoString* arg1);
// ## Generated Code ##
	};
};