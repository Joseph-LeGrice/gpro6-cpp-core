#pragma once

#include <type_traits>
#include "DataStructures\PODArray.h"

template<typename T>
struct ComponentArray
{
    PODArray<T> m_components;

    ComponentArray()
    {
        m_components = PODArray<T>::New();
    }

    ~ComponentArray()
    {
        PODArray<T>::Free(m_components);
    }

    int InsertComponent(T& newComp)
    {
        static_assert(std::is_pod<T>::value, "Component must be a POD type!");

        int newIndex = (int)PODArray<T>::Size(m_components);
        PODArray<T>::Push_Back(m_components, newComp);
        return newIndex;
    }

    void RemoveComponent(int index)
    {
        if (index >= 0 && index < m_components.size())
        {
            size_t lastIndex = m_components.size() - 1;
            m_components[index] = m_components[lastIndex];
            PODArray<T>::Resize(m_components, lastIndex);
        }
    }

    T* const GetArrayPointer()
    {
        return PODArray<T>::GetArrayPointer(m_components);
    }

    size_t GetArraySize()
    {
        return PODArray<T>::Size(m_components);
    }
};