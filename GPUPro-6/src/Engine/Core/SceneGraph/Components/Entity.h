#pragma once

#include "Engine/Core/SceneGraph/IComponent.h"
#include "Engine/Core/SceneGraph/Components/Util/ComponentReferenceNode.h"

#include <vector>
#include "Engine/Core/SceneGraph/SceneGraph.hpp"
#include "Engine/Core/SceneGraph/IComponent.h"

static const unsigned int c_numberOfComponentTypesAllowed = 10;

struct Entity : IComponent
{
    ComponentReferenceNode* m_rootNode;
    ComponentReferenceNode m_nodePool[c_numberOfComponentTypesAllowed];
    bool m_activeNodeIndexPool[c_numberOfComponentTypesAllowed];
    unsigned int m_currentNumberOfNodesActive;

	Entity(int componentIndex) : IComponent(componentIndex)
	{
		for (size_t i = 0; i < c_numberOfComponentTypesAllowed; i++)
		{
			m_activeNodeIndexPool[i] = false;
			InitComponentReferenceNode(m_nodePool[i]);
		}

		m_currentNumberOfNodesActive = 0;
		m_rootNode = nullptr;
	}

	static ComponentTypeID GetComponentType() {
		return 5;
	}

	template<class T>
	T& AddComponent(SceneGraph& sceneGraph)
	{
		T& newComponent = sceneGraph.CreateComponent<T>();
		LinkComponent<T>(newComponent);
		return newComponent;
	}

	template<class T>
	void RemoveComponent(SceneGraph& sceneGraph)
	{
		T* component = GetComponent<T>();
		UnlinkComponent(component);
		sceneGraph.DeleteComponent(component->m_componentIndex);
	}

	template<class T>
	T* GetComponent(SceneGraph& sceneGraph)
	{
		int componentIndex = GetComponentIndex();
		return sceneGraph.GetComponent<T>(componentIndex);
	}

	template<class T>
	void LinkComponent(T& component)
	{
		if (m_currentNumberOfNodesActive < c_numberOfComponentTypesAllowed - 1)
		{
			ComponentReferenceNode* nodeInserted = Insert(GetComponentType(), component.m_componentIndex, m_rootNode);
			component.m_entityIndex = ec.m_componentIndex;

			if (nodeInserted != nullptr && ec.m_data.m_rootNode == nullptr)
			{
				ec.m_data.m_rootNode = nodeInserted;
			}
		}
	}

	template<class T>
	void UnlinkComponent(T& component)
	{
		Delete(GetComponentType(), component.m_componentIndex, m_rootNode);
		component.m_entityIndex = -1;
	}

	int GetComponentIndex()
	{
		ComponentReferenceNode* nodeFound = Find(GetComponentType(), m_rootNode);
		if (nodeFound != nullptr && nodeFound->m_currentSize > 0)
		{
			return nodeFound->m_componentIndices[0];
		}
		else
		{
			return -1;
		}
	}

	template<typename T>
	std::vector<int> GetComponentIndices()
	{
		ComponentReferenceNode* nodeFound = Find(GetComponentType(), m_rootNode);
		return GetIndices(nodeFound);
	}

private:
	ComponentReferenceNode* GetNextNode();
	void ReturnNode(ComponentReferenceNode* node);

	ComponentReferenceNode* Insert(ComponentTypeID ct, size_t i, ComponentReferenceNode* currentNode);
	ComponentReferenceNode* Delete(ComponentTypeID ct, size_t i, ComponentReferenceNode* currentNode);
	ComponentReferenceNode* Find(ComponentTypeID ct, ComponentReferenceNode* currentNode);
	ComponentReferenceNode* Rebalance(ComponentReferenceNode* currentNode);
};

