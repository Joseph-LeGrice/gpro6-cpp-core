#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(std::vector<ResourceTypeID> resourceTypes, GraphicsDevice& gfxDevice) : m_resourceReferences(gfxDevice, *this)
{
	m_resourceListMap = std::unordered_map<ResourceTypeID, std::vector<IResource*>>();
	for (auto it = resourceTypes.begin(); it != resourceTypes.end(); it++)
	{
		m_resourceListMap.insert({ *it, std::vector<IResource*>() });
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
