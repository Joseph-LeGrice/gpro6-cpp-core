#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

struct ResourceManagerAPI
{
	static MonoObject* CreateResource(MonoString* className);
	//static void DestroyResource(MonoType* object); //TODO
	//static MonoArray* GetAllResourcesOfType(MonoType resourceType); //TODO
	//static MonoObject* GetResource(int resourceIndex); //TODO

	static void RegisterMonoMethods();
};