#include "stdafx.h"
#include "Entity.h"


ComponentReferenceNode* Entity::GetNextNode()
{
    int index = m_currentNodeIndex;
    m_currentNodeIndex++;
    return &m_nodePool[index];
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
        ComponentReferenceNode& nodeRef = *currentNode;

        if (ti == nodeRef.m_componentType)
        {
            AddIndex(nodeRef, i);
            return currentNode;
        }
        else if (ti < nodeRef.m_componentType)
        {
            nodeRef.m_leftChild = Insert(ti, i, nodeRef.m_leftChild);
        }
        else if (ti > nodeRef.m_componentType)
        {
            nodeRef.m_rightChild = Insert(ti, i, nodeRef.m_rightChild);
        }

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
}