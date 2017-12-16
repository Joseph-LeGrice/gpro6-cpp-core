#pragma once

#include <vector>
#include <tuple>

template<class... Types>
class ResourceManagerDefinition
{
    //TODO: Ideally should be storing some structure which allows for grouping the memory together such that assets 'relevant' to each other exists near to each other.

private:
    std::tuple<std::vector<Types>...> m_allResources;

public:
    template<class T>
    T* Instantiate()
    {
        std::vector<T>& resources = std::get<std::vector<T>>(m_allResources);
        int index = static_cast<int>(resources.size());
        resources.resize(index + 1, T(index));
        return &resources[index];
    }

    template<class T>
    T* GetAsset(int index)
    {
        std::vector<T>& resources = std::get<std::vector<T>>(m_allResources);
        if (index > -1 && index < resources.size())
        {
            return &resources[index];
        }
        else
        {
            return nullptr;
        }
    }

    template<class T>
    void DeallocateAll()
    {
        std::vector<T>& resources = std::get<std::vector<T>>(m_allResources);
        for (size_t i = 0; i < resources.size(); i++)
        {
            resources[i].Release();
        }
        resources.clear();
    }

    template<class T>
    void Deallocate(int index)
    {
        std::vector<T>& resources = std::get<std::vector<T>>(m_allResources);
        int lastIndex = static_cast<int>(resources.size()) - 1;
        T& deletedAsset = resources[index];
        deletedAsset.Release();

        resources[index] = resources[lastIndex];
        resources[lastIndex] = deletedAsset;
        resources.resize(lastIndex);
    }
};
