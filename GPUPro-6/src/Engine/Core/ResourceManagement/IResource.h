#pragma once
#include "Engine/Core/Scripting/ManagedObject.h"
#include "Engine/Core/RTTI/ITypedObject.h"

class IResource : public ITypedObject
{
	friend class ResourceManager;

public:
	IResource();
	virtual ~IResource();

	virtual void Initialize();
	virtual void Release();

	ManagedObject* GetManagedObject(); // TODO: Remove this - binding a managed + native object should be easy to configure and require no extra code

private:
	ManagedObject* m_managedObject = nullptr;
};
