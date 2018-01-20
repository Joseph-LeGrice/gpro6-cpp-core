#pragma once

#include "Material.hpp"

template<>
class Material<void> : public IResource
{
public:
    struct ResourceDetails
    {
        int m_resourceIndex;
        int m_slotIndex;
    };

    Material(int resourceId) : IResource(resourceId) { }
    Material() : IResource() { }
    ~Material() { }

    bool BindIfValid();

    void SetShaderIndex(UINT16 shaderIndex)
    {
        m_shaderIndex = shaderIndex;
    }

    void RegisterShaderResource(ResourceDetails rd)
    {
        m_shaderResources.push_back(rd);
    }

    void AddTextureSampler(ResourceDetails rd)
    {
        m_textureSamplerIndexes.push_back(rd);
    }

    void Release() override
    {
    }

private:
    int m_shaderIndex = -1;
    std::vector<ResourceDetails> m_shaderResources;
    std::vector<ResourceDetails> m_textureSamplerIndexes;
};

typedef Material<void> SimpleMaterial;
