#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace Texture2DArrayAPI
	{
// ## Generated Code ##
		extern void RegisterCalls();

		extern void InitializeWithBitmaps(int managedInstanceId, MonoArray* arg0);

		extern int GetResourceViewID(int managedInstanceId);
// ## Generated Code ##
	};
};