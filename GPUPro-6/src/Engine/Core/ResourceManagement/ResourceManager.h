#pragma once

#include <unordered_map>
#include "IResource.h"
#include "ResourceTypeMapping.h"

class GraphicsDevice;

class ResourceManager
{
public:
	~ResourceManager(); 

	IResource* CreateResource(ResourceTypeID typeId);
	void DestroyResource(ResourceTypeID typeId, int index);
	std::vector<IResource*> GetAllResourcesOfType(ResourceTypeID typeId);
	IResource* GetResource(ResourceTypeID typeId, size_t arrayIndex);

	template<class T>
	T* CreateResource();

	template<class T>
	void DestroyResource(int index);

	template<class T>
	T* GetResource(size_t arrayIndex);

	template<class T>
	std::vector<T*> GetAllResourcesOfType();

private:
	std::unordered_map<ResourceTypeID, std::vector<IResource*>> m_resourceListMap;
};

template<class T>
T* ResourceManager::CreateResource()
{
	ResourceTypeID typeId = T::GetResourceTypeID();
	return static_cast<T*>(CreateResource(typeId));
}

template<class T>
void ResourceManager::DestroyResource(int index)
{
	ResourceTypeID typeId = T::GetResourceTypeID();
	DestroyResource(typeId, index);
}

template<class T>
std::vector<T*> ResourceManager::GetAllResourcesOfType()
{
	struct CastComponent { T* operator ()(IResource* value) const { return static_cast<T*>(value); } };

	ResourceTypeID typeId = T::GetResourceType();
	std::vector<T*> result = GetAllResourcesOfType(typeId);
	std::transform(existing.begin(), existing.end(), result.begin(), CastComponent());
	return result;
}

template<class T>
T* ResourceManager::GetResource(size_t arrayIndex)
{
	ResourceTypeID typeId = T::GetResourceTypeID();
	IResource* result = GetResource(typeId, arrayIndex);
	if (result != nullptr)
	{
		return static_cast<T*>(result);
	}
	else
	{
		return nullptr;
	}
}