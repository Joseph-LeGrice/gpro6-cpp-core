#pragma once

#include <vector>
#include <typeindex>
#include <type_traits>
#include <unordered_map>

typedef std::vector<size_t> IndexList;
typedef std::unordered_map<std::type_index, IndexList> IndexMap;

struct Entity
{
	template<class T>
	void RegisterComponent(size_t index)
	{
		m_componentIndexMap[typeid(T)].push_back(index);
	}

	template<typename T>
	IndexList GetIndicesForComponent()
	{
		std::type_index ti = typeid(T);
		if (m_componentIndexMap.count(ti))
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
