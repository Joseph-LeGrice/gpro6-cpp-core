#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

struct ScriptedSystemInterface
{
	static void RegisterSystemInstance(MonoObject* object);

	static void RegisterMonoMethods();
};