#pragma once

#include "Engine/Core/SceneGraph/IComponent.h"
#include "Engine/Core/SceneGraph/Components/Util/ComponentReferenceNode.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

#include <vector>
#include "Engine/Core/SceneGraph/SceneGraph.hpp"
#include "Engine/Core/SceneGraph/IComponent.h"

static const unsigned int c_numberOfComponentTypesAllowed = 10;

struct Entity : public ITypedObject
{
	REGISTER_TYPE(Entity);
    ComponentReferenceNode* m_rootNode;
    ComponentReferenceNode m_nodePool[c_numberOfComponentTypesAllowed];
    bool m_activeNodeIndexPool[c_numberOfComponentTypesAllowed];
    unsigned int m_currentNumberOfNodesActive;

	Entity()
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
	T& AddComponent(TypedObjectManager& typedObjectManager)
	{
		T& newComponent = typedObjectManager.Create<T>();
		LinkComponent<T>(newComponent);
		return newComponent;
	}

	template<class T>
	void RemoveComponent(TypedObjectManager& typedObjectManager)
	{
		T* component = GetComponent<T>();
		UnlinkComponent(component);
		typedObjectManager.Delete<T>(component->GetInstanceID());
	}

	template<class T>
	T* GetComponent(TypedObjectManager& typedObjectManager)
	{
		int componentIndex = GetComponentIndex();
		return typedObjectManager.GetInstance<T>(componentIndex);
	}

	template<class T>
	void LinkComponent(T& component)
	{
		if (m_currentNumberOfNodesActive < c_numberOfComponentTypesAllowed - 1)
		{
			ComponentReferenceNode* nodeInserted = Insert(GetComponentType(), component.GetInstanceID(), m_rootNode);
			component.m_entityIndex = GetInstanceID();

			if (nodeInserted != nullptr && m_data.m_rootNode == nullptr)
			{
				m_data.m_rootNode = nodeInserted;
			}
		}
	}

	template<class T>
	void UnlinkComponent(T& component)
	{
		Delete(GetComponentType(), component.GetInstanceID(), m_rootNode);
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

