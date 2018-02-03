#pragma once

#include <type_traits>

const size_t c_maximumComponents = 250;

template<typename T>
struct ComponentArray
{    
    int InsertComponent(T& newComp)
    {
        if (m_currentSize < c_maximumComponents)
        {
            int newIndex = static_cast<int>(m_currentSize);
            memcpy(&m_components[newIndex], &newComp, sizeof(T));
            m_currentSize++;
            return newIndex;
        }
        else
        {
            return -1;
        }
    }

    void RemoveComponent(int index)
    {
        if (index < m_currentSize)
        {
            size_t lastIndex = m_currentSize - 1;
            m_components[index] = m_components[lastIndex];
            m_components[index].m_componentIndex = index;
            m_currentSize--;
        }
    }

    T* const GetArrayPointer()
    {
        return m_components;
    }

    size_t GetArraySize()
    {
        return m_currentSize;
    }

private:
    T m_components[c_maximumComponents];
    size_t m_currentSize = 0;
};