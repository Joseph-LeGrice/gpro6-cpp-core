#pragma once

#include <vector>
#include <tuple>
#include "Graphics/ResourceTypes/Shader.h"
#include "Graphics/ResourceTypes/Material.h"
#include "Graphics/ResourceTypes/Texture2D.h"
#include "Graphics/ResourceTypes/Texture2DArray.h"
#include "Graphics/ResourceTypes/StructuredBuffer.h"
#include "Graphics/ResourceTypes/TextureSampler.h"
#include "Graphics/ResourceTypes/Mesh.h"

template<class... Types>
class AssetManagerImpl
{
public:

    //TODO: Ideally should be storing some structure which allows for grouping the memory together such that assets 'relevant' to each other exists near to each other.

    std::tuple<std::vector<Types>...> m_assetLists;

    template<class T>
    T* Instantiate()
    {
        std::vector<T>& assetList = std::get<std::vector<T>>(m_assetLists);
        int index = static_cast<int>(assetList.size());
        assetList.resize(index + 1, T(index));
        return &assetList[index];
    }

    template<class T>
    T* GetAsset(int index)
    {
        std::vector<T>& assetList = std::get<std::vector<T>>(m_assetLists);
        if (index > -1 && index < assetList.size())
        {
            return &assetList[index];
        }
        else
        {
            return nullptr;
        }
    }

    template<class T>
    void Deallocate(int index)
    {
        std::vector<T>& assetList = std::get<std::vector<T>>(m_assetLists);
        int lastIndex = static_cast<int>(assetList.size()) - 1;
        T& deletedAsset = assetList[index];
        assetList[index] = assetList[lastIndex];
        assetList[lastIndex] = deletedAsset;
        assetList.resize(lastIndex);
    }
};

typedef AssetManagerImpl<
    Shader,
    Mesh,
    TextureSampler,
    Texture2D,
    Texture2DArray,
    StructuredBuffer,
    Material
> AssetManager;

extern AssetManager* s_instance;

AssetManager& GetAssetManager();
void DestroyAssetManager();
