#include "stdafx.h"
#include "Entity.h"

ComponentReferenceNode* Entity::GetNextNode()
{
    if (m_currentNumberOfNodesActive < c_numberOfComponentTypesAllowed - 1)
    {
        for (size_t i = 0; i < c_numberOfComponentTypesAllowed; i++)
        {
            if (!m_activeNodeIndexPool[i])
            {
                m_activeNodeIndexPool[i] = true;
                m_currentNumberOfNodesActive++;

                InitComponentReferenceNode(m_nodePool[i]);
                return &m_nodePool[i];
            }
        }
    }
    return nullptr;
}

void Entity::ReturnNode(ComponentReferenceNode* node)
{
    int nodeIndex = -1;
    for (size_t i = 0; i < c_numberOfComponentTypesAllowed; i++)
    {
        if (&m_nodePool[i] == node)
        {
            nodeIndex = static_cast<int>(i);
        }
    }

    m_currentNumberOfNodesActive--;
    m_activeNodeIndexPool[nodeIndex] = false;
}

ComponentReferenceNode* Entity::Insert(ComponentTypeID ct, size_t i, ComponentReferenceNode* currentNode)
{
    if (currentNode == nullptr)
    {
        ComponentReferenceNode* nextNode = GetNextNode();
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
            currentNode->m_leftChild = Insert(ct, i, currentNode->m_leftChild);
        }
        else if (ct > currentNode->m_componentType)
        {
            currentNode->m_rightChild = Insert(ct, i, currentNode->m_rightChild);
        }

        return Rebalance(currentNode);
    }
}

ComponentReferenceNode* Entity::Find(ComponentTypeID ct, ComponentReferenceNode* currentNode)
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

ComponentReferenceNode* Entity::Delete(ComponentTypeID ct, size_t i, ComponentReferenceNode* currentNode)
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
            ReturnNode(currentNode);
            return newChild;
        }
    }

    ComponentReferenceNode* newChild = nullptr;
    if (ct < currentNode->m_componentType)
    {
        newChild = Delete(ct, i, currentNode->m_leftChild);
        if (newChild != nullptr)
        {
            currentNode->m_leftChild = newChild;
        }
    }
    else if (ct > currentNode->m_componentType)
    {
        newChild = Delete(ct, i, currentNode->m_rightChild); 
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

ComponentReferenceNode* Entity::Rebalance(ComponentReferenceNode* currentNode)
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