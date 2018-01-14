#pragma once
#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"

namespace EntityUtil
{
    template<class T>
    T& AddComponent(EntityComponent& e)
    {
        T& newComponent = GetSceneGraph().CreateComponent<T>();
        LinkComponent<T>(e, newComponent);
        return newComponent;
    }

    template<class T>
    void RemoveComponent(EntityComponent& e)
    {
        T* component = GetComponent<T>(e);
        UnlinkComponent(e, component);
        GetSceneGraph().DeleteComponent(component->m_componentIndex);
    }

    template<class T>
    T* GetComponent(EntityComponent& e)
    {
        int componentIndex = GetComponentIndex<T>(e);
        return GetSceneGraph().GetComponent<T>(componentIndex);
    }

    template<class T>
    void LinkComponent(EntityComponent& ec, T& component)
    {
        if (ec.m_data.m_currentNumberOfNodesActive < c_numberOfComponentTypesAllowed - 1)
        {
            ComponentReferenceNode* nodeInserted = EntityInternal::Insert(ec.m_data, GetComponentType<T>(), component.m_componentIndex, ec.m_data.m_rootNode);
            component.m_entityIndex = ec.m_componentIndex;

            if (nodeInserted != nullptr && ec.m_data.m_rootNode == nullptr)
            {
                ec.m_data.m_rootNode = nodeInserted;
            }
        }
    }

    template<class T>
    void UnlinkComponent(EntityComponent& ec, T& component)
    {
        EntityInternal::Delete(ec.m_data, GetComponentType<T>(), component.m_componentIndex, ec.m_data.m_rootNode);
        component.m_entityIndex = -1;
    }

    template<typename T>
    int GetComponentIndex(EntityComponent& ec)
    {
        ComponentReferenceNode* nodeFound = EntityInternal::Find(GetComponentType<T>(), ec.m_data.m_rootNode);
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
    std::vector<int> GetComponentIndices(EntityComponent& ec)
    {
        ComponentReferenceNode* nodeFound = EntityInternal::Find(GetComponentType<T>(), ec.m_data.m_rootNode);
        return GetIndices(nodeFound);
    }
}
