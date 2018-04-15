#pragma once

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/object.h>
#pragma warning(pop)

typedef uint16_t ResourceTypeID;

class IResource
{
	friend class ResourceManager;

public:
	IResource();
	virtual ~IResource();

	virtual void Release() = 0;
	virtual const char* GetName() = 0;

	MonoObject* GetManagedObject();

	size_t GetResourceIndex();

private:
	size_t m_resourceIndex;
	uint32_t m_objectHandle;

	void ConstructManagedObject();
};
