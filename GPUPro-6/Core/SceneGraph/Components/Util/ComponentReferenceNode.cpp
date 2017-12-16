#include "stdafx.h"
#include "ComponentReferenceNode.h"

void InitComponentReferenceNode(ComponentReferenceNode& node)
{
    node.m_componentType = NULL;
    node.m_height = 0;
    node.m_leftChild = nullptr;
    node.m_rightChild = nullptr;
    node.m_currentSize = 0;
    for (size_t i = 0; i < c_maxComponentsOfSameType; i++)
    {
        node.m_componentIndices[i] = -1;
    }
}

std::vector<size_t> GetIndices(ComponentReferenceNode* node)
{
    std::vector<size_t> result;
    if (node != nullptr)
    {
        for (size_t i = 0; i < node->m_currentSize; i++)
        {
            result.push_back(node->m_componentIndices[i]);
        }
    }
    return result;
}

int GetBalance(ComponentReferenceNode& node)
{
    return LeftHeight(node) - RightHeight(node);
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

bool RemoveIndex(ComponentReferenceNode& node, size_t index)
{
    int indexOfIndex = -1;
    for (int i = 0; i < node.m_currentSize; i++)
    {
        if (node.m_componentIndices[i] == index)
        {
            indexOfIndex = i;
            break;
        }
    }

    if (indexOfIndex > -1)
    {
        node.m_componentIndices[indexOfIndex] = node.m_componentIndices[node.m_currentSize - 1];
        node.m_currentSize = node.m_currentSize - 1;
    }
    return indexOfIndex > -1;
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

ComponentReferenceNode* DeleteNode(ComponentReferenceNode* node)
{
    if (node->m_leftChild != nullptr && node->m_rightChild != nullptr)
    {
        ComponentReferenceNode* replacementNode = FindMin(node->m_rightChild);
        replacementNode->m_leftChild = node->m_leftChild;
        return replacementNode;
    }
    else
    {
        if (node->m_leftChild != nullptr)
        {
            return node->m_leftChild;
        }
        else if (node->m_rightChild != nullptr)
        {
            return node->m_rightChild;
        }
        else
        {
            return nullptr;
        }
    }
}

ComponentReferenceNode* FindMax(ComponentReferenceNode* node)
{
    if (node->m_rightChild != nullptr)
    {
        return FindMax(node->m_rightChild);
    }
    else
    {
        return node;
    }
}

ComponentReferenceNode* FindMin(ComponentReferenceNode* node)
{
    if (node->m_leftChild != nullptr)
    {
        return FindMin(node->m_leftChild);
    }
    else
    {
        return node;
    }
}
