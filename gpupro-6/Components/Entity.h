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
        if (m_currentNodeIndex < c_numberOfComponentTypesAllowed - 1)
        {
            Insert(typeid(T), componentIndex, m_rootNode);
        }
	}

    template<class T>
    void RemoveComponentIndex(size_t componentIndex)
    {
        Delete(typeid(T), componentIndex, m_rootNode);
    }

	template<typename T>
	std::vector<int> GetComponentIndices()
    {
        ComponentReferenceNode* nodeFound = Find(typeid(T), m_rootNode);
        return GetIndices(nodeFound);
	}

private:
    ComponentReferenceNode m_rootNode;
    ComponentReferenceNode m_nodePool[c_numberOfComponentTypesAllowed];
    unsigned int m_currentNodeIndex = 0;
    
    ComponentReferenceNode* GetNextNode();
    void ReturnNode(ComponentReferenceNode* node);
    ComponentReferenceNode* Insert(std::type_index ti, size_t i, ComponentReferenceNode* currentNode);

    ComponentReferenceNode* Rebalance(ComponentReferenceNode* currentNode);

    ComponentReferenceNode* Find(std::type_index ti, ComponentReferenceNode* currentNode);
    ComponentReferenceNode* Delete(std::type_index ti, size_t i, ComponentReferenceNode* currentNode);
};
