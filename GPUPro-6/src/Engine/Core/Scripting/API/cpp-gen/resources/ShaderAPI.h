#pragma once

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

		extern void InitVertexShader(int managedInstanceId, MonoString* arg0, MonoString* arg1);

		extern void InitPixelShader(int managedInstanceId, MonoString* arg0, MonoString* arg1);

		extern void InitGeometryShader(int managedInstanceId, MonoString* arg0, MonoString* arg1);

		extern void InitHullShader(int managedInstanceId, MonoString* arg0, MonoString* arg1);

		extern void InitDomainShader(int managedInstanceId, MonoString* arg0, MonoString* arg1);
// ## Generated Code ##
	};
};