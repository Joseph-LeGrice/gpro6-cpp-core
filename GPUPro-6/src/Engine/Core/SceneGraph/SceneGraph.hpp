#pragma once

#include <vector>
#include <algorithm>
#include <unordered_map>

#include "IComponent.h"

static const auto component_map = [] { return "component_map"; };

class SceneGraph
{
public:
	template<class T>
	std::vector<T*> GetComponentArrayPointer()
	{
		struct CastComponent { T* operator ()(IComponent* value) const { return dynamic_cast<T*>(value); } };
		
		ComponentTypeID typeId = T::GetComponentType();
		if (m_componentListMap.count(typeId) > 0)
		{
			std::vector<IComponent*>& existing = m_componentListMap[typeId];
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
	T* GetComponent(int index)
	{
		ComponentTypeID typeId = T::GetComponentType();
		if (m_componentListMap.count(typeId) > 0)
		{
			std::vector<IComponent*>& existing = m_componentListMap[typeId];
			return dynamic_cast<T*>(existing[index]);
		}
		else
		{
			return nullptr;
		}
	}

	template<class T>
	void DeleteComponent(int index)
	{
		ComponentTypeID typeId = T::GetComponentType();
		if (m_componentListMap.count(typeId) > 0)
		{
			std::vector<IComponent*>& components = m_componentListMap[typeId];
			size_t length = components->size();
			components[index] = components[length - 1];
			components.resize(length - 1);
		}
	}

	template<class T>
	T* CreateComponent()
	{
		ComponentTypeID typeId = T::GetComponentType();
		if (m_componentListMap.count(typeId) > 0)
		{
			std::vector<IComponent*>& components = m_componentListMap[typeId];

			int index = components.size();
			T newComponent = new T(index);
			components.push_back(newComponent);

			return components[index];
		}
		else
		{
			return nullptr;
		}
	}

	SceneGraph(std::vector<ComponentTypeID> componentList)
	{
		m_componentListMap = std::unordered_map<ComponentTypeID, std::vector<IComponent*>>();
		for (auto it = componentList.begin(); it != componentList.end(); it++)
		{
			m_componentListMap.insert({ *it, std::vector<IComponent*>() });
		}
	}
	~SceneGraph() = default;

private:
	std::unordered_map<ComponentTypeID, std::vector<IComponent*>> m_componentListMap;
};
