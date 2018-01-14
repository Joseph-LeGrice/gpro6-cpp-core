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
    struct ResourceDetails
    {
        int m_resourceIndex; //TODO: Shoukd never be able to bind an invalid or non existant resource here.
        size_t m_slotIndex;
    };

	Material(UINT resouceId);
	~Material();

    bool BindIfValid();
	
    void SetShaderIndex(UINT16 shaderIndex);
	
    void AddTexture2DResource(ResourceDetails rd);
    void AddTexture2DArrayResource(ResourceDetails rd);
    void AddStructuredBufferResource(ResourceDetails rd);
	void AddTextureSampler(ResourceDetails rd);

    virtual void Release() override;


private:
    int m_shaderIndex;
    std::vector<ResourceDetails> m_texture2dIndexes;
    std::vector<ResourceDetails> m_texture2dArrayIndexes;
    std::vector<ResourceDetails> m_structuredBufferIndexes;
	std::vector<ResourceDetails> m_textureSamplerIndexes;
};
