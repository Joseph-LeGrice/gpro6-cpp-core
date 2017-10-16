#pragma once

#include "D3D11.h"
#include <string>
#include <vector>
#include <unordered_map>

struct Mesh;
class Shader;
class ShaderResource;
class VertexBuffer;
class IndexBuffer;
class ShaderResource;
class TextureSampler;
struct Matrix4x4;

typedef std::unordered_map<size_t, std::vector<size_t>> MeshTransformMap;

class Material
{
public:
	~Material();

	static Material* Create();

	void Render(Matrix4x4&,Matrix4x4&);
	void UpdateIfDirty();
	
	void SetShader(Shader* shader, size_t numberOfResources, size_t numberOfSamplers);
	
	void DeregisterMeshInfo(size_t meshIndex, size_t transformIndex);
	void RegisterMeshInfo(size_t meshIndex, size_t transformIndex);
	
	void AddShaderResource(size_t shaderResourceIndex, size_t shaderResourceSlotIndex);
	void RemoveShaderResource(size_t shaderResourceSlotIndex);

	void AddTextureSampler(size_t textureSamplerIndex, size_t textureSamplerSlotIndex);
	void RemoveTextureSampler(size_t textureSamplerSlotIndex);

private:
	bool Initialize();

	Material();
	Material(const Material&) = delete;

	bool m_isDirty;
	Shader* m_shader;
	size_t m_numberOfResources;
	size_t m_numberOfSamplers;
	
	std::vector<size_t> m_shaderResourceIndexes;
	std::vector<size_t> m_textureSamplerIndexes;
	
	VertexBuffer* m_myVertexBuffer;
	IndexBuffer* m_myIndexBuffer;
	MeshTransformMap m_renderMap;
};
