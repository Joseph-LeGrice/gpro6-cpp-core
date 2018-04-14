#pragma once

#include <unordered_map>
#include "IResource.h"
#include "ResourceTypeMapping.h"

class GraphicsDevice;

class ResourceManager
{
public:
	template<class T>
	std::vector<T*> GetAllAssetsOfType()
	{
		struct CastComponent { T* operator ()(IResource* value) const { return static_cast<T*>(value); } };

		ResourceTypeID typeId = T::GetResourceType();
		if (m_resourceListMap.count(typeId) > 0)
		{
			std::vector<IResource*>& existing = m_resourceListMap[typeId];
			std::vector<T*> result;
			std::transform(existing.begin(), existing.end(), result.begin(), CastComponent());
			return result;
		}
		else
		{
			return std::vector<T*>();
		}
	}

	template<class T>
	T* GetAsset(size_t arrayIndex)
	{
		ResourceTypeID typeId = T::GetResourceTypeID();
		if (m_resourceListMap.count(typeId) > 0)
		{
			std::vector<IResource*>& existing = m_resourceListMap[typeId];
			if (existing.size() > 0 && arrayIndex < existing.size())
			{
				return static_cast<T*>(existing[arrayIndex]);
			}
		}
		return nullptr;
	}

	IResource* Instantiate(ResourceTypeID typeId)
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

	template<class T>
	T* Instantiate()
	{
		ResourceTypeID typeId = T::GetResourceTypeID();
		return static_cast<T*>(Instantiate(typeId));
	}

	template<class T>
	void Deallocate(int index)
	{
		ResourceTypeID typeId = T::GetResourceTypeID();
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

	~ResourceManager();

private:
	std::unordered_map<ResourceTypeID, std::vector<IResource*>> m_resourceListMap;
};
