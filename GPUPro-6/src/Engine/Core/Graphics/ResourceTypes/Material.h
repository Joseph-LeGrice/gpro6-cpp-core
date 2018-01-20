#pragma once

#include <vector>
#include "Engine/Core/ResourceManagement/IResource.h"

class Material : public IResource
{
public:
    struct ResourceDetails
    {
        int m_resourceIndex;
        int m_slotIndex;
    };

    Material(UINT resourceId) : IResource(resourceId) { }
    Material() : IResource() { }
    ~Material() { }

    bool BindIfValid();
    void SetShaderIndex(UINT16 shaderIndex);
    void RegisterShaderResource(ResourceDetails rd);
    void AddTextureSampler(ResourceDetails rd);
    virtual void Release() override;

private:
    int m_shaderIndex = -1;
    
    std::vector<ResourceDetails> m_shaderResources;
	std::vector<ResourceDetails> m_textureSamplerIndexes;
};
