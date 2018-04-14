#include "stdafx.h"
#include "ResourceManager.h"

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
