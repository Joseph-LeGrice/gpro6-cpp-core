#include "stdafx.h"
#include "ComponentReferenceNode.h"

int GetBalance(ComponentReferenceNode& node)
{
    return RightHeight(node) - LeftHeight(node);
}

int RightHeight(ComponentReferenceNode& node)
{
    return node.m_rightChild != nullptr ? node.m_rightChild->m_height : -1;
}

int LeftHeight(ComponentReferenceNode& node)
{
    return node.m_leftChild != nullptr ? node.m_leftChild->m_height : -1;
}

bool AddIndex(ComponentReferenceNode& node, size_t index)
{
    if (node.m_currentSize < c_maxComponentsOfSameType - 1)
    {
        int newIndex = static_cast<int>(index);
        bool foundExisting = false;
        for (int i = 0; i < node.m_currentSize; i++)
        {
            foundExisting |= node.m_componentIndices[i] == newIndex;
        }

        if (!foundExisting)
        {
            node.m_componentIndices[node.m_currentSize] = newIndex;
            node.m_currentSize++;
            return true;
        }
    }
    return false;
}

void DetermineHeight(ComponentReferenceNode& node)
{
    if (node.m_leftChild != nullptr && node.m_rightChild != nullptr)
    {
        node.m_height = 1 + (node.m_leftChild->m_height >= node.m_rightChild->m_height ? node.m_leftChild->m_height : node.m_rightChild->m_height);
    }
    else if (node.m_leftChild != nullptr)
    {
        node.m_height = node.m_leftChild->m_height + 1;
    }
    else if (node.m_rightChild != nullptr)
    {
        node.m_height = node.m_rightChild->m_height + 1;
    }
    else
    {
        node.m_height = 0;
    }
}

ComponentReferenceNode* RotateLeft(ComponentReferenceNode& node)
{
    if (node.m_rightChild != nullptr)
    {
        ComponentReferenceNode* rightNode = node.m_rightChild;
        node.m_rightChild = rightNode->m_leftChild;
        rightNode->m_leftChild = &node;
        return rightNode;
    }
    return nullptr;
}

ComponentReferenceNode* RotateRight(ComponentReferenceNode& node)
{
    if (node.m_leftChild != nullptr)
    {
        ComponentReferenceNode* leftNode = node.m_leftChild;
        node.m_leftChild = leftNode->m_rightChild;
        leftNode->m_rightChild = &node;
        return leftNode;
    }
    return nullptr;
}