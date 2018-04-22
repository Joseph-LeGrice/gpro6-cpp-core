#pragma once

#include <unordered_map>
#include "IResource.h"
#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

class ResourceManager
{
public:
	IResource* CreateResource(TypeID typeId);
	void DestroyResource(TypeID typeId, InstanceID objId);

	template<class T>
	T* CreateResource();

	template<class T>
	void DestroyResource(InstanceID objId);

	template<class T>
	T* GetResource(InstanceID objId);

	template<class T>
	std::vector<T*> GetAllResourcesOfType();
};

template<class T>
T* ResourceManager::CreateResource()
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	T* newResource = tom->Create<T>();
	newResource->Initialize();
	return newResource;
}

template<class T>
void ResourceManager::DestroyResource(InstanceID objId)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	T* resource = tom->GetInstance<T>(objId);
	resource->Release();
	tom->Delete<T>(objId);
}

template<class T>
std::vector<T*> ResourceManager::GetAllResourcesOfType()
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	return tom->GetAllInstances<T>();
}

template<class T>
T* ResourceManager::GetResource(InstanceID objId)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	return tom->GetInstance<T>(objId);
}