#pragma once

#include <vector>
#include <typeindex>
#include <type_traits>
#include <unordered_map>

typedef std::vector<size_t> IndexList;
typedef std::unordered_map<std::type_index, IndexList> IndexMap;

struct Entity
{
public:
	template<class T>
	void Entity::RegisterComponent(Entity& e, size_t index)
	{
		m_componentIndexMap[typeid(T)].push_back(index);
	}

	template<typename T>
	static IndexList Entity::GetIndicesForComponent(Entity& e)
	{
		std::type_index ti = typeid(T);
		if (e.m_componentIndexMap.count(ti))
		{
			return m_componentIndexMap[ti];
		}
		else
		{
			return std::vector<size_t>();
		}
	}

private:
	IndexMap m_componentIndexMap;
};
