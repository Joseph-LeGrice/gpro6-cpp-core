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

	static int Create();

	bool BindIfValid();
	
	void SetShader(Shader* shader, size_t numberOfResources, size_t numberOfSamplers);
	
	void AddShaderResource(int shaderResourceIndex, size_t shaderResourceSlotIndex);
	void RemoveShaderResource(size_t shaderResourceSlotIndex);

	void AddTextureSampler(int textureSamplerIndex, size_t textureSamplerSlotIndex);
	void RemoveTextureSampler(size_t textureSamplerSlotIndex);

private:
	Material();
	Material(const Material&) = delete;

	Shader* m_shader;
	size_t m_numberOfResources;
	size_t m_numberOfTextureSamplers;
	std::vector<int> m_shaderResourceIndexes;
	std::vector<int> m_textureSamplerIndexes;
};
