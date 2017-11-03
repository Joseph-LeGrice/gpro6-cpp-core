#pragma once

#include <vector>
#include <typeindex>
#include <type_traits>

#include "DataStructures/Util/ComponentReferenceNode.h"

static const unsigned int c_numberOfComponentTypesAllowed = 10;

struct Entity
{
	template<class T>
	void AddComponent(size_t componentIndex)
	{
	}

    template<class T>
    void RemoveComponentIndex(size_t componentIndex)
    {
    }

	template<typename T>
	std::vector<int> GetComponentIndices()
    {
        return std::vector<size_t>();
	}

private:
    ComponentReferenceNode m_rootNode;
    ComponentReferenceNode m_nodePool[c_numberOfComponentTypesAllowed];
    unsigned int m_currentNodeIndex = 0;
    
    ComponentReferenceNode* GetNextNode();
    ComponentReferenceNode* Insert(std::type_index ti, size_t i, ComponentReferenceNode* currentNode);
};
