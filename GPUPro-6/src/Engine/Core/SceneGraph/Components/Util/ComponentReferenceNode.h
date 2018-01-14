#pragma once

#include <vector>
#include "Engine/Core/SceneGraph/Components/Util/ComponentType.hpp"


static const unsigned int c_maxComponentsOfSameType = 10;

struct ComponentReferenceNode
{
    ComponentType m_componentType;

    int m_height;
    ComponentReferenceNode* m_leftChild;
    ComponentReferenceNode* m_rightChild;

    int m_componentIndices[c_maxComponentsOfSameType];
    int m_currentSize;
};

void InitComponentReferenceNode(ComponentReferenceNode& node);
std::vector<size_t> GetIndices(ComponentReferenceNode* node);
int GetBalance(ComponentReferenceNode& node);
int RightHeight(ComponentReferenceNode& node);
int LeftHeight(ComponentReferenceNode& node);
bool AddIndex(ComponentReferenceNode& node, size_t index);
bool RemoveIndex(ComponentReferenceNode& node, size_t index);
void DetermineHeight(ComponentReferenceNode& node);
ComponentReferenceNode* RotateLeft(ComponentReferenceNode& node);
ComponentReferenceNode* RotateRight(ComponentReferenceNode& node);
ComponentReferenceNode* DeleteNode(ComponentReferenceNode* node);
ComponentReferenceNode* FindMax(ComponentReferenceNode* node); 
ComponentReferenceNode* FindMin(ComponentReferenceNode* node);