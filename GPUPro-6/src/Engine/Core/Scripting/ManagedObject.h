#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)
#include "Engine/Core/RTTI/ITypedObject.h"

typedef uint32_t ManagedObjectID;

class ManagedObject : public ITypedObject
{
friend class ScriptedSystemLoader;
public:
	~ManagedObject();

	MonoObject* GetManagedObject();
	void SetFieldValue(const char* fieldName, void* value);

	virtual const char* GetTypeName() override
	{
		return TO_STRING(ManagedObject);
	}

private:
	ManagedObjectID m_objectHandle;
};
REGISTER_TYPE(ManagedObject, 42);
