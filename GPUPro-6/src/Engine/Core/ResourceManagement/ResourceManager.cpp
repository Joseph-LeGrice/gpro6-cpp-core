#include "stdafx.h"
#include "ResourceManager.h"

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

IResource* ResourceManager::CreateResource(ResourceTypeID typeId)
{
	if (m_resourceListMap.count(typeId) > 0)
	{
		std::vector<IResource*>& resources = m_resourceListMap[typeId];

		size_t index = resources.size();
		IResource* newResource = ResourceTypeMappings::CreateType(typeId);
		newResource->m_resourceIndex = index;
		resources.push_back(newResource);

		return resources[index];
	}
	else
	{
		return nullptr;
	}
}

void ResourceManager::DestroyResource(ResourceTypeID typeId, int index)
{
	if (m_resourceListMap.count(typeId) > 0)
	{
		std::vector<IResource*>& resources = m_resourceListMap[typeId];
		size_t length = resources.size();

		resources[index]->Release();
		delete resources[index];

		resources[index] = resources[length - 1];
		resources[index]->m_resourceIndex = index;

		resources.resize(length - 1);
	}
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
	if (m_resourceListMap.count(typeId) > 0)
	{
		std::vector<IResource*>& existing = m_resourceListMap[typeId];
		if (existing.size() > 0 && arrayIndex < existing.size())
		{
			return existing[arrayIndex];
		}
	}
	return nullptr;
}
