#include "stdafx.h"
#include "Entity.h"

ComponentReferenceNode* EntityInternal::GetNextNode(Entity& e)
{
    if (e.m_currentNumberOfNodesActive < c_numberOfComponentTypesAllowed - 1)
    {
        for (size_t i = 0; i < c_numberOfComponentTypesAllowed; i++)
        {
            if (!e.m_activeNodeIndexPool[i])
            {
                e.m_activeNodeIndexPool[i] = true;
                e.m_currentNumberOfNodesActive++;

                InitComponentReferenceNode(e.m_nodePool[i]);
                return &e.m_nodePool[i];
            }
        }
    }
    return nullptr;
}

void EntityInternal::ReturnNode(Entity& e, ComponentReferenceNode* node)
{
    int nodeIndex = -1;
    for (size_t i = 0; i < c_numberOfComponentTypesAllowed; i++)
    {
        if (&e.m_nodePool[i] == node)
        {
            nodeIndex = static_cast<int>(i);
        }
    }

    e.m_currentNumberOfNodesActive--;
    e.m_activeNodeIndexPool[nodeIndex] = false;
}

ComponentReferenceNode* EntityInternal::Insert(Entity& e, ComponentType ct, size_t i, ComponentReferenceNode* currentNode)
{
    if (currentNode == nullptr)
    {
        ComponentReferenceNode* nextNode = GetNextNode(e);
        nextNode->m_height = 0;
        nextNode->m_componentType = ct;
        AddIndex(*nextNode, i);

        return nextNode;
    }
    else
    {
        if (ct == currentNode->m_componentType)
        {
            AddIndex(*currentNode, i);
            return currentNode;
        }
        else if (ct < currentNode->m_componentType)
        {
            currentNode->m_leftChild = Insert(e, ct, i, currentNode->m_leftChild);
        }
        else if (ct > currentNode->m_componentType)
        {
            currentNode->m_rightChild = Insert(e, ct, i, currentNode->m_rightChild);
        }

        return Rebalance(currentNode);
    }
}

ComponentReferenceNode* EntityInternal::Find(ComponentType ct, ComponentReferenceNode* currentNode)
{
    if (currentNode == nullptr)
    {
        return nullptr;
    }
    else if (ct > currentNode->m_componentType)
    {
        return Find(ct, currentNode->m_rightChild);
    }
    else if (ct < currentNode->m_componentType)
    {
        return Find(ct, currentNode->m_leftChild);
    }
    else
    {
        return currentNode;
    }
}

ComponentReferenceNode* EntityInternal::Delete(Entity& e, ComponentType ct, size_t i, ComponentReferenceNode* currentNode)
{
    if (currentNode == nullptr)
    {
        return nullptr;
    }
    else if (ct == currentNode->m_componentType)
    {
        if (currentNode->m_currentSize > 1)
        {
            RemoveIndex(*currentNode, i);
            return nullptr;
        }
        else
        {
            ComponentReferenceNode* newChild = DeleteNode(currentNode);
            ReturnNode(e, currentNode);
            return newChild;
        }
    }

    ComponentReferenceNode* newChild = nullptr;
    if (ct < currentNode->m_componentType)
    {
        newChild = Delete(e, ct, i, currentNode->m_leftChild);
        if (newChild != nullptr)
        {
            currentNode->m_leftChild = newChild;
        }
    }
    else if (ct > currentNode->m_componentType)
    {
        newChild = Delete(e, ct, i, currentNode->m_rightChild); 
        if (newChild != nullptr)
        {
            currentNode->m_rightChild = newChild;
        }
    }
    
    if (newChild != nullptr)
    {
        return Rebalance(currentNode);
    }
    else
    {
        return nullptr;;
    }
}

ComponentReferenceNode* EntityInternal::Rebalance(ComponentReferenceNode* currentNode)
{
    ComponentReferenceNode& nodeRef = *currentNode;
    DetermineHeight(nodeRef);

    int balance = GetBalance(nodeRef);
    if (balance > 1 && nodeRef.m_componentType < nodeRef.m_leftChild->m_componentType)
    {
        return RotateRight(nodeRef);
    }
    else if (balance < -1 && nodeRef.m_componentType > nodeRef.m_rightChild->m_componentType)
    {
        return RotateLeft(nodeRef);
    }
    else if (balance > 1 && nodeRef.m_componentType > nodeRef.m_leftChild->m_componentType)
    {
        nodeRef.m_leftChild = RotateLeft(*nodeRef.m_leftChild);
        return RotateRight(nodeRef);
    }
    else if (balance < -1 && nodeRef.m_componentType < nodeRef.m_rightChild->m_componentType)
    {
        nodeRef.m_rightChild = RotateRight(*nodeRef.m_rightChild);
        return RotateLeft(nodeRef);
    }
    else
    {
        return currentNode;
    }
}