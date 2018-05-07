#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

namespace GPro
{
	namespace Texture2DAPI
	{
		extern void RegisterCalls();
		extern void InitializeWithBitmap(int managedInstanceId, const wchar_t* arg0);
	};
};