#pragma once

#include "Components/ComponentType.hpp"
#include "DataStructures/Util/ComponentReferenceNode.h"

#include <vector>

static const unsigned int c_numberOfComponentTypesAllowed = 10;

struct Entity
{
    Entity();
    Entity(const Entity&) = delete;
    ~Entity();

	template<class T>
	void AddComponent(size_t componentIndex)
	{
        if (m_currentNumberOfNodesActive < c_numberOfComponentTypesAllowed - 1)
        {
            Insert(GetComponentType<T>(), componentIndex, m_rootNode);
        }
	}

    template<class T>
    void RemoveComponentIndex(size_t componentIndex)
    {
        Delete(GetComponentType<T>(), componentIndex, m_rootNode);
    }

	template<typename T>
	std::vector<int> GetComponentIndices()
    {
        ComponentReferenceNode* nodeFound = Find(GetComponentType<T>(), m_rootNode);
        return GetIndices(nodeFound);
	}

private:
    ComponentReferenceNode* m_rootNode;
    ComponentReferenceNode m_nodePool[c_numberOfComponentTypesAllowed];
    bool m_activeNodeIndexPool[c_numberOfComponentTypesAllowed];
    unsigned int m_currentNumberOfNodesActive = 0;
    
    ComponentReferenceNode* GetNextNode();
    void ReturnNode(ComponentReferenceNode* node);

    ComponentReferenceNode* Insert(ComponentType ct, size_t i, ComponentReferenceNode* currentNode);
    ComponentReferenceNode* Find(ComponentType ct, ComponentReferenceNode* currentNode);
    ComponentReferenceNode* Delete(ComponentType ct, size_t i, ComponentReferenceNode* currentNode);
    ComponentReferenceNode* Rebalance(ComponentReferenceNode* currentNode);
};
