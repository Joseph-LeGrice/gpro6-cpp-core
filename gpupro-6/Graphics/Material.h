#pragma once

#include "D3D11.h"
#include <string>
#include <vector>
#include <unordered_map>

class Shader;

typedef std::unordered_map<size_t, std::vector<size_t>> MeshTransformMap;

class Material
{
public:
    struct ResourceDetails
    {
        int m_resourceIndex;
        size_t m_slotIndex;
    };

	~Material();
	Material();
	Material(const Material&) = delete;

    bool BindIfValid();
	
    void SetShader(Shader* shader);
	
    void AddTexture2DResource(ResourceDetails rd);
    void AddStructuredBufferResource(ResourceDetails rd);
	void AddTextureSampler(ResourceDetails rd);
	
private:
	Shader* m_shader;
    std::vector<ResourceDetails> m_texture2dIndexes;
    std::vector<ResourceDetails> m_structuredBufferIndexes;
	std::vector<ResourceDetails> m_textureSamplerIndexes;
};
