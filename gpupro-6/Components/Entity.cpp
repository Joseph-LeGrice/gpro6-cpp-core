#include "stdafx.h"
#include "Entity.h"


ComponentReferenceNode* Entity::GetNextNode()
{
    if (m_currentNodeIndex < c_numberOfComponentTypesAllowed - 1)
    {
        int index = m_currentNodeIndex;
        m_currentNodeIndex++;
        return &m_nodePool[index];
    }
    else
    {
        return nullptr;
    }
}

void Entity::ReturnNode(ComponentReferenceNode* node)
{

}

ComponentReferenceNode* Entity::Insert(std::type_index ti, size_t i, ComponentReferenceNode* currentNode)
{
    if (currentNode == nullptr)
    {
        ComponentReferenceNode* nextNode = GetNextNode();
        nextNode->m_height = 1;
        nextNode->m_componentType = ti;
        AddIndex(*nextNode, i);

        return nextNode;
    }
    else
    {
        if (ti == currentNode->m_componentType)
        {
            AddIndex(*currentNode, i);
            return currentNode;
        }
        else if (ti < currentNode->m_componentType)
        {
            currentNode->m_leftChild = Insert(ti, i, currentNode->m_leftChild);
        }
        else if (ti > currentNode->m_componentType)
        {
            currentNode->m_rightChild = Insert(ti, i, currentNode->m_rightChild);
        }

        return Rebalance(currentNode);

    }
}

ComponentReferenceNode* Entity::Find(std::type_index ti, ComponentReferenceNode* currentNode)
{
    if (currentNode == nullptr)
    {
        return nullptr;
    }
    else if (ti > currentNode->m_componentType)
    {
        return Find(ti, currentNode->m_rightChild);
    }
    else if (ti < currentNode->m_componentType)
    {
        return Find(ti, currentNode->m_leftChild);
    }
    else
    {
        return currentNode;
    }
}

ComponentReferenceNode* Entity::Delete(std::type_index ti, size_t i, ComponentReferenceNode* currentNode)
{
    if (currentNode == nullptr)
    {
        return nullptr;
    }
    else if (ti == currentNode->m_componentType)
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
    if (ti < currentNode->m_componentType)
    {
        newChild = Delete(ti, i, currentNode->m_leftChild);
        if (newChild != nullptr)
        {
            currentNode->m_leftChild = newChild;
        }
    }
    else if (ti > currentNode->m_componentType)
    {
        newChild = Delete(ti, i, currentNode->m_rightChild); 
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