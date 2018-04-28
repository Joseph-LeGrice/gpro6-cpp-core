#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)
#include "Engine/Core/RTTI/ITypedObject.h"

typedef uint32_t ManagedObjectHandle;

class ManagedObject : public ITypedObject
{
friend class ScriptedSystemLoader;
REGISTER_TYPE(ManagedObject);
public:
	~ManagedObject();

	MonoObject* GetManagedObject();
	void SetFieldValue(const char* fieldName, void* value);

private:
	//ManagedTypeID m_typeId;
	ManagedObjectHandle m_objectHandle = 0;
};
