#pragma once

#include "D3D11.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "Graphics/ConstantBuffers/PerObjectBuffer.h"

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
	
	void SetShader(Shader* shader);
	
	void DeregisterMeshInfo(size_t meshIndex, size_t transformIndex);
	void RegisterMeshInfo(size_t meshIndex, size_t transformIndex);
	
	void AddShaderResource(ShaderResource* r);
	void RemoveShaderResource(ShaderResource* r);

	void AddTextureSampler(TextureSampler* ts);
	void RemoveTextureSampler(TextureSampler* ts);

private:
	bool Initialize();

	Material();
	Material(const Material&) = delete;

	bool m_isDirty;
	Shader* m_shader;
	std::vector<ShaderResource*> m_shaderResources; //TODO: Contiguous array of all ShaderResources. Reference via index
	std::vector<TextureSampler*> m_textureSamplers; //TODO: Contiguous array of all TextureSamplers. Reference via index

	VertexBuffer* m_myVertexBuffer;
	IndexBuffer* m_myIndexBuffer;
	MeshTransformMap m_renderMap;
};
