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
        e.m_rootNode = nullptr;
        return e;
    }
};

typedef ComponentRegistrationInfo<Entity, 5, InitEntity> EntityComponent;

template<class T>
void LinkComponent(EntityComponent& ec, T& component)
{
    if (ec.m_data.m_currentNumberOfNodesActive < c_numberOfComponentTypesAllowed - 1)
    {
        ComponentReferenceNode* nodeInserted = Insert(ec.m_data, GetComponentType<T>(), component.m_componentIndex, ec.m_data.m_rootNode);
        component.m_entityIndex = ec.m_componentIndex;

        if (nodeInserted != nullptr && ec.m_data.m_rootNode == nullptr)
        {
            ec.m_data.m_rootNode = nodeInserted;
        }
    }
}

template<class T>
void UnlinkComponent(EntityComponent& ec, T& component)
{
    Delete(ec.m_data, GetComponentType<T>(), component.m_componentIndex, ec.m_data.m_rootNode);
    component.m_entityIndex = -1;
}

template<typename T>
int GetComponentIndex(EntityComponent& ec)
{
    ComponentReferenceNode* nodeFound = Find(GetComponentType<T>(), ec.m_data.m_rootNode);
    if (nodeFound != nullptr && nodeFound->m_currentSize > 0)
    {
        return nodeFound->m_componentIndices[0];
    }
    else
    {
        return -1;
    }
}

template<typename T>
std::vector<int> GetComponentIndices(EntityComponent& ec)
{
    ComponentReferenceNode* nodeFound = Find(GetComponentType<T>(), ec.m_data.m_rootNode);
    return GetIndices(nodeFound);
}
