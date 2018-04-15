#include "stdafx.h"
#include "ResourceManager.h"
#include "ResourceTypeMapping.h"

ResourceManager::~ResourceManager()
{
	for (auto mapIt = m_resourceListMap.begin(); mapIt != m_resourceListMap.end(); mapIt++)
	{
		auto list = mapIt->second;
		for (int i = 0; i < list.size(); i++)
		{
			list[i]->Release();
			delete list[i];
		}
	}
}

std::vector<IResource*>& ResourceManager::GetResourceList(ResourceTypeID typeId)
{
	if (m_resourceListMap.count(typeId) > 0)
	{
		return m_resourceListMap[typeId];
	}
	else
	{
		std::vector<IResource*> newVector;
		m_resourceListMap.insert({ typeId, newVector });
		return m_resourceListMap[typeId];
	}
}

IResource* ResourceManager::CreateResource(ResourceTypeID typeId)
{
	std::vector<IResource*>& resources = GetResourceList(typeId);

	size_t index = resources.size();
	IResource* newResource = ResourceTypeMappings::Instance().CreateType(typeId);
	newResource->m_resourceIndex = index;
	newResource->ConstructManagedObject();
	resources.push_back(newResource);

	return resources[index];
}

void ResourceManager::DestroyResource(ResourceTypeID typeId, int index)
{
	std::vector<IResource*>& resources = GetResourceList(typeId);
	size_t length = resources.size();

	resources[index]->Release();
	resources[index]->ReleaseManagedObject();
	delete resources[index];

	resources[index] = resources[length - 1];
	resources[index]->m_resourceIndex = index;

	resources.resize(length - 1);
}

std::vector<IResource*> ResourceManager::GetAllResourcesOfType(ResourceTypeID typeId)
{
	if (m_resourceListMap.count(typeId) > 0)
	{
		return m_resourceListMap[typeId];
	}
	else
	{
		return std::vector<IResource*>();
	}
}

IResource* ResourceManager::GetResource(ResourceTypeID typeId, size_t arrayIndex)
{
	std::vector<IResource*>& resources = GetResourceList(typeId);

	if (resources.size() > 0 && arrayIndex < resources.size())
	{
		return resources[arrayIndex];
	}
	else
	{
		return nullptr;
	}
}
