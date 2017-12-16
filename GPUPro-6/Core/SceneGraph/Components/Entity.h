#pragma once

#include "Core/SceneGraph/Components/Util/ComponentType.hpp"
#include "Core/SceneGraph/Components/Util/ComponentReferenceNode.h"

#include <vector>

static const unsigned int c_numberOfComponentTypesAllowed = 10;

struct Entity
{
    ComponentReferenceNode* m_rootNode;
    ComponentReferenceNode m_nodePool[c_numberOfComponentTypesAllowed];
    bool m_activeNodeIndexPool[c_numberOfComponentTypesAllowed];
    unsigned int m_currentNumberOfNodesActive;
};

namespace EntityInternal
{
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
}

typedef ComponentRegistrationInfo<Entity, 5, EntityInternal::InitEntity> EntityComponent;
