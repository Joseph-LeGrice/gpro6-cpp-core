#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

class Texture2DAPI
{
	static void RegisterCalls();
	static void InitializeWithBitmap(int managedInstanceId, const wchar_t* arg0);
};