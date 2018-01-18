#pragma once

#include "D3D11.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "Engine/Core/ResourceManagement/IResource.h"

class Shader;

typedef std::unordered_map<size_t, std::vector<size_t>> MeshTransformMap;

class Material : public IResource
{
public:

    struct ShaderResourceDetails
    {
        UINT m_resourceIndex;
        size_t m_slotIndex;
    };

    struct SamplerDetails
    {
        UINT m_resourceIndex;
        size_t m_slotIndex;
    };

	Material(UINT resouceId);
	~Material();

    bool BindIfValid();
	
    void SetShaderIndex(UINT16 shaderIndex);
	
    void RegisterShaderResource(ShaderResourceDetails rd);
    void AddTextureSampler(SamplerDetails rd);

    virtual void Release() override;


private:
    int m_shaderIndex;
    std::vector<ShaderResourceDetails> m_shaderResources;
	std::vector<SamplerDetails> m_textureSamplerIndexes;
};
