#pragma once

#include <vector>
#include <typeindex>
#include <type_traits>

static const unsigned int c_maxComponentsOfSameType = 10;
static const unsigned int c_numberOfComponentTypesAllowed = 10;

struct Entity
{
	template<class T>
	void AddComponent(size_t componentIndex)
	{
	}

    template<class T>
    void RemoveComponentIndex(size_t componentIndex)
    {
    }

	template<typename T>
	std::vector<int> GetComponentIndices()
    {
        return std::vector<size_t>();
	}

private:
    struct ComponentReferenceNode
    {
        std::type_index m_componentType;

        int m_height = -1;
        ComponentReferenceNode* m_leftChild = nullptr;
        ComponentReferenceNode* m_rightChild = nullptr;

        int m_componentIndices[c_maxComponentsOfSameType];
        int m_currentSize = 0;

        bool IsUnbalanced()
        {
            int heightDiff = RightHeight() - LeftHeight();
            return heightDiff * heightDiff > 1;
        }

        int RightHeight()
        {
            return m_rightChild != nullptr ? m_rightChild->m_height : -1;
        }

        int LeftHeight()
        {
            return m_leftChild != nullptr ? m_leftChild->m_height : -1;
        }

        bool AddIndex(size_t index)
        {
            if (m_currentSize < c_maxComponentsOfSameType - 1)
            {
                int newIndex = static_cast<int>(index);
                bool foundExisting = false;
                for (int i = 0; i < m_currentSize; i++)
                {
                    foundExisting |= m_componentIndices[i] == newIndex;
                }

                if (!foundExisting)
                {
                    m_componentIndices[m_currentSize] = newIndex;
                    m_currentSize++;
                    return true;
                }
            }
            return false;
        }

        void DetermineHeight()
        {
            if (m_leftChild != nullptr && m_rightChild != nullptr)
            {
                m_height = 1 + (m_leftChild->m_height >= m_rightChild->m_height ? m_leftChild->m_height : m_rightChild->m_height);
            }
            else if (m_leftChild != nullptr)
            {
                m_height = m_leftChild->m_height + 1;
            }
            else if (m_rightChild != nullptr)
            {
                m_height = m_rightChild->m_height + 1;
            }
            else
            {
                m_height = 0;
            }
        }

        void RotateLeft()
        {
            if (m_rightChild != nullptr)
            {
                ComponentReferenceNode* rightNode = m_rightChild;
                m_rightChild = rightNode->m_leftChild;
                rightNode->m_leftChild = this;
            }
        }

        void RotateRight()
        {
            if (m_leftChild != nullptr)
            {
                ComponentReferenceNode* leftNode = m_leftChild;
                m_leftChild = leftNode->m_rightChild;
                leftNode->m_rightChild = this;
            }
        }
    };

    ComponentReferenceNode m_rootNode;
    ComponentReferenceNode m_nodePool[c_numberOfComponentTypesAllowed];
    unsigned int m_currentNodeIndex = 0;

    bool Insert(std::type_index ti, size_t i, ComponentReferenceNode& currentNode)
    {
        if (ti == currentNode.m_componentType)
        {
            currentNode.AddIndex(i);
            return false; // Only return true if we need to update the heights
        }
        else if (ti < currentNode.m_componentType)
        {
            if (currentNode.m_leftChild == nullptr)
            {
                ComponentReferenceNode& nextNode = *GetNextNode();
                nextNode.m_height = 1;
                nextNode.m_componentType = ti;
                nextNode.AddIndex(i);
                currentNode.m_leftChild = &nextNode;

                return true;
            }
            else if (Insert(ti, i, *currentNode.m_leftChild))
            {
                currentNode.DetermineHeight();

                if (currentNode.m_leftChild.IsUnbalanced())
                {

                }

                return true;
            }
        }
        else if (ti > currentNode.m_componentType)
        {
            if (currentNode.m_rightChild == nullptr)
            {
                ComponentReferenceNode& nextNode = *GetNextNode();
                nextNode.m_height = 1;
                nextNode.m_componentType = ti;
                nextNode.AddIndex(i);
                currentNode.m_rightChild = &nextNode;

                return true;
            }
            else if (Insert(ti, i, *currentNode.m_rightChild))
            {
                currentNode.DetermineHeight();

                return true;
            }
        }
        return false;
    }

    ComponentReferenceNode* GetNextNode()
    {
        int index = m_currentNodeIndex;
        m_currentNodeIndex++;
        return &m_nodePool[index];
    }
};
    