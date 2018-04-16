#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

struct Logging
{
	static void LogMessage(MonoString* message);
	//static void LogWarning(MonoString* message); // TODO
	//static void LogError(MonoString* message); // TODO

	static void RegisterMonoMethods();
};