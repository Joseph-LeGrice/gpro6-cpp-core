#pragma once

#include <vector>
#include <tuple>

template<class... Types>
class ResourceManagerDefinition
{
public:
    template<class T>
    T* Instantiate()
    {
        std::vector<T>& resources = std::get<std::vector<T>>(m_allResources);
        int arrayIndex = static_cast<int>(resources.size());
        resources.resize(arrayIndex + 1, T(arrayIndex));
        return &resources[arrayIndex];
    }

    template<class T>
    T* GetAsset(int arrayIndex)
    {
        std::vector<T>& resources = std::get<std::vector<T>>(m_allResources);
        return &resources[arrayIndex];
    }

    template<class T>
    void Deallocate(int arrayIndex)
    {
        std::vector<T>& resources = std::get<std::vector<T>>(m_allResources);
        int lastIndex = static_cast<int>(resources.size()) - 1;
        T& deletedAsset = resources[arrayIndex];
        deletedAsset.Release();

        resources[arrayIndex] = resources[lastIndex];
        resources[lastIndex] = deletedAsset;
        resources.resize(lastIndex);
    }

    template<int I = 0>
    inline typename std::enable_if<I == sizeof...(Types), void>::type
        DeallocateAll()
    {}

    template<int I = 0>
    inline typename std::enable_if < I < sizeof...(Types), void>::type
        DeallocateAll()
    {
        auto resources = std::get<I>(m_allResources);
        for (size_t i = 0; i < resources.size(); i++)
        {
            resources[i].Release();
        }
        resources.clear();
        DeallocateAll<I + 1>();
    }

private:
    std::tuple<std::vector<Types>...> m_allResources;
};

