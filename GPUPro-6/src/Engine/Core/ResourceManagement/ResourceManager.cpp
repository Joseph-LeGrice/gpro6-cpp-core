#include "stdafx.h"
#include "ResourceManager.h"

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

ResourceManager::~ResourceManager()
{
	for (auto mapIt = m_resourceListMap.begin(); mapIt != m_resourceListMap.end(); mapIt++)
	{
		auto list = mapIt->second;
		for (int i=0; i<list.size(); i++)
		{
			list[i]->Release();
			delete list[i];
		}
	}
}
