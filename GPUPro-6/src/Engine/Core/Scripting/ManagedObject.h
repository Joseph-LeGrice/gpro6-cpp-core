#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

typedef uint32_t ManagedObjectID;

class ManagedObject
{
public:
	MonoObject* GetManagedObject();
	void SetFieldValue(const char* fieldName, void* value);

	static ManagedObject* ConstructManagedObject(const char* className);
	static void ReleaseManagedObject(ManagedObject**);

private:
	ManagedObjectID m_objectHandle;

	ManagedObject(ManagedObjectID objId) : m_objectHandle(objId) { }
};
