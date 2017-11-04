
#include <typeindex>
#include <vector>

static const unsigned int c_maxComponentsOfSameType = 10;

struct ComponentReferenceNode
{
    std::type_index m_componentType;

    int m_height = -1;
    ComponentReferenceNode* m_leftChild = nullptr;
    ComponentReferenceNode* m_rightChild = nullptr;

    int m_componentIndices[c_maxComponentsOfSameType];
    int m_currentSize = 0;
};

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