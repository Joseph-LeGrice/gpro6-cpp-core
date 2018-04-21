#pragma once
#include "Engine/Core/Scripting/ManagedObject.h"

typedef uint16_t ResourceTypeID;

class IResource
{
	friend class ResourceManager;

public:
	IResource();
	virtual ~IResource();

	virtual void Initialize();
	virtual void Release();
	virtual const char* GetName() = 0;

	ManagedObject* GetManagedObject();
	size_t GetResourceIndex();

private:
	ManagedObject* m_managedObject = nullptr;
	size_t m_resourceIndex;

	void SetResourceIndex(size_t resourceIndex);
};
