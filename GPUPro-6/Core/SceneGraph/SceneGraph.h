#pragma once

#include "Core/Graphics/Components/Camera.h"
#include "Core/Graphics/Components/Transform.h"
#include "Core/Graphics/Components/MeshRenderer.h"
#include "Core/Graphics/Components/Light.h"
#include "Core/SceneGraph/Components/Entity.h"
#include "Extra/TransformSync/TranslationSync.h"

#include "Core/SceneGraph/Components/Util/ComponentArray.hpp"
#include <vector>
#include <tuple>

template<typename... Types>
struct SceneGraphImpl
{
    static_assert(is_registered_typelist<Types...>::value, "Type list contains a non ComponentRegistrationInfo instantiation.");
    static_assert(does_not_collide<Types...>::value, "A component in the type list has a type id collision");
    
    template<class T>
    T* const GetComponentArrayPointer()
    {
        static_assert(is_registered<T>::value, "T is not registered component type");
        return std::get<ComponentArray<T>>(m_componentArrays).GetArrayPointer();
    }

    template<class T>
    size_t GetNumberOfComponents()
    {
        static_assert(is_registered<T>::value, "T is not registered component type");
        return std::get<ComponentArray<T>>(m_componentArrays).GetArraySize();
    }

    template<class T>
    T* GetComponent(int index)
    {
        static_assert(is_registered<T>::value, "T is not registered component type");

        ComponentArray<T>& ca = std::get<ComponentArray<T>>(m_componentArrays);
        if (index >= 0 && index < ca.GetArraySize())
        {
            T* arrayPointer = ca.GetArrayPointer();
            return &arrayPointer[index];
        }
        else
        {
            return nullptr;
        }
    }

    template<class T>
    void DeleteComponent(int index)
    {
        static_assert(is_registered<T>::value, "T is not registered component type");

        ComponentArray<T>& ca = std::get<ComponentArray<T>>(m_componentArrays);
        ca.RemoveComponent(index);
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
        
        T* arrayPointer = ca.GetArrayPointer();

        int i = ca.InsertComponent(newComponent);
        T& result = arrayPointer[i];
        result.m_componentIndex = i;
        return result;
    }

    SceneGraphImpl() = default;
    ~SceneGraphImpl() = default;
    SceneGraphImpl(SceneGraphImpl&) = delete;

private:
    std::tuple<ComponentArray<Types>...> m_componentArrays;
};

typedef SceneGraphImpl<
    TransformComponent,
    CameraComponent,
    MeshRendererComponent,
    EntityComponent,
    LightComponent,
    TranslationSyncComponent
> SceneGraph;

SceneGraph& GetSceneGraph();
