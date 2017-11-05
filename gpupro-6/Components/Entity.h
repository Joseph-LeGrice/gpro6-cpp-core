#pragma once

#include "Components/ComponentType.hpp"
#include "DataStructures/Util/ComponentReferenceNode.h"

#include <vector>

static const unsigned int c_numberOfComponentTypesAllowed = 10;

struct Entity
{
    ComponentReferenceNode* m_rootNode;
    ComponentReferenceNode m_nodePool[c_numberOfComponentTypesAllowed];
    bool m_activeNodeIndexPool[c_numberOfComponentTypesAllowed];
    unsigned int m_currentNumberOfNodesActive;
};

template<class T>
void AddComponent(Entity& e, size_t componentIndex)
{
    if (m_currentNumberOfNodesActive < c_numberOfComponentTypesAllowed - 1)
    {
        Insert(e, GetComponentType<T>(), componentIndex, e.m_rootNode);
    }
}

template<class T>
void RemoveComponentIndex(Entity& e, size_t componentIndex)
{
    Delete(e, GetComponentType<T>(), componentIndex, e.m_rootNode);
}

template<typename T>
std::vector<int> GetComponentIndices(Entity& e)
{
    ComponentReferenceNode* nodeFound = Find(GetComponentType<T>(), e.m_rootNode);
    return GetIndices(nodeFound);
}

ComponentReferenceNode* GetNextNode(Entity& e);
void ReturnNode(Entity& e, ComponentReferenceNode* node);

ComponentReferenceNode* Insert(Entity& e, ComponentType ct, size_t i, ComponentReferenceNode* currentNode);
ComponentReferenceNode* Delete(Entity& e, ComponentType ct, size_t i, ComponentReferenceNode* currentNode);
ComponentReferenceNode* Find(ComponentType ct, ComponentReferenceNode* currentNode);
ComponentReferenceNode* Rebalance(ComponentReferenceNode* currentNode);

struct InitEntity
{
    Entity operator()()
    {
        Entity e;
        for (size_t i = 0; i < c_numberOfComponentTypesAllowed; i++)
        {
            e.m_activeNodeIndexPool[i] = false;
            InitComponentReferenceNode(e.m_nodePool[i]);
        }

        e.m_currentNumberOfNodesActive = 0;
        e.m_rootNode = GetNextNode(e);
    }
};

typedef ComponentRegistrationInfo<Entity, 5, InitEntity> EntityComponent;