#pragma once

#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace MeshHelperAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern MonoObject* CreateSphereUV_Internal();

		extern MonoObject* CreateQuad_Internal();
// ## Generated Code ##
	};
};