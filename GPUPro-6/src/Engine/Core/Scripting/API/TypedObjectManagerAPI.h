#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

struct TypedObjectManagerAPI
{
	static MonoObject* Create(MonoString* className);
	//static void Delete(MonoType* object); //TODO
	//static MonoArray* GetAllResourcesOfType(MonoType resourceType); //TODO
	//static MonoObject* GetInstance(int resourceIndex); //TODO

	static void RegisterMonoMethods();
};