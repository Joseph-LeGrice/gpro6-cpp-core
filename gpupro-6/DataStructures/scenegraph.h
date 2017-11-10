#pragma once

#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/MeshRenderer.h"
#include "Components/Light.h"
#include "Components/Entity.h"

#include "DataStructures/ComponentArray.hpp"
#include <vector>
#include <tuple>

template<typename... Types>
struct SceneGraphImpl
{
    std::tuple<ComponentArray<Types>...> m_componentArrays;
 
    template<class T>
    ComponentArray<T>& GetComponentArray()
    {
        static_assert(is_registered<T>::value, "T is not registered component type");
        return std::get<ComponentArray<T>>(m_componentArrays);
    }

    template<class T>
    T* GetComponent(int index)
    {
        static_assert(is_registered<T>::value, "T is not registered component type");

        ComponentArray<T>& ca = std::get<ComponentArray<T>>(m_componentArrays);
        if (index >= 0 && index < ca.GetArraySize())
        {
            return &ca.m_components[index];
        }
        else
        {
            return nullptr;
        }
    }

    template<class T>
    T& CreateComponent()
    {
        static_assert(is_registered<T>::value, "T is not registered component type");

        ComponentArray<T>& ca = std::get<ComponentArray<T>>(m_componentArrays);
        T newComponent;
        newComponent.m_componentIndex = -1;
        newComponent.m_entityIndex = -1;
        newComponent.m_data = newComponent.s_initFunctor();
        
        int i = ca.InsertComponent(newComponent);
        T& result = ca.m_components[i];
        result.m_componentIndex = i;
        return result;
    }

    SceneGraphImpl() = default;
    ~SceneGraphImpl() = default;
    SceneGraphImpl(SceneGraphImpl&) = delete;
};

typedef SceneGraphImpl<
    TransformComponent,
    CameraComponent,
    LightComponent,
    MeshRendererComponent,
    EntityComponent
> SceneGraph;


SceneGraph& GetSceneGraph();
