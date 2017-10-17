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
	~Material();

	static size_t Create();

	void Bind();
	
	void SetShader(Shader* shader, size_t numberOfResources, size_t numberOfSamplers);
	
	void AddShaderResource(size_t shaderResourceIndex, size_t shaderResourceSlotIndex);
	void RemoveShaderResource(size_t shaderResourceSlotIndex);

	void AddTextureSampler(size_t textureSamplerIndex, size_t textureSamplerSlotIndex);
	void RemoveTextureSampler(size_t textureSamplerSlotIndex);

private:
	Material();
	Material(const Material&) = delete;

	Shader* m_shader;
	std::vector<size_t> m_shaderResourceIndexes;
	std::vector<size_t> m_textureSamplerIndexes;
};
