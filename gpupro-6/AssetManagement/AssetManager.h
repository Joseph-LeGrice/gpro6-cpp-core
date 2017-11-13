#pragma once

#include <vector>
#include <tuple>
#include "Graphics/Shader.h"
#include "Graphics/Material.h"
#include "Graphics/ResourceTypes/Texture2D.h"
#include "Graphics/ResourceTypes/StructuredBuffer.h"
#include "Graphics/TextureSampler.h"
#include "DataStructures/Mesh.h"

template<class... Types>
class AssetManagerImpl
{
public:

    //TODO: Should not be storing lists of pointers. At the very least it should be lists of the actual type (although this doesn't allow for templated types).
    //TODO: Ideally should be storing some structure which allows for grouping the memory together such that assets 'relevant' to each other exists near to each other.

    std::tuple<std::vector<Types*>...> m_assetLists;

    template<class T>
    int AllocateNew()
    {
        std::vector<T*>& assetList = std::get<std::vector<T*>>(m_assetLists);
        int index = static_cast<int>(assetList.size());
        assetList.resize(index + 1);
        assetList[index] = new T();
        return index;
    }

    template<class T>
    T* GetAsset(int index)
    {
        std::vector<T*>& assetList = std::get<std::vector<T*>>(m_assetLists);
        return assetList[index];
    }

    template<class T>
    void Deallocate(int index)
    {
        std::vector<T*>& assetList = std::get<std::vector<T*>>(m_assetLists);
        int lastIndex = static_cast<int>(assetList.size()) - 1;
        delete assetList[index];
        assetList[index] = assetList[lastIndex];
        assetList.resize(lastIndex);
    }
};

typedef AssetManagerImpl<
    Shader,
    Mesh,
    TextureSampler,
    Texture2D,
    StructuredBuffer,
    Material
> AssetManager;

AssetManager& GetAssetManager();
