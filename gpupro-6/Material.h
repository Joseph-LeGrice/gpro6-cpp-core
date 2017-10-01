#pragma once

#include "D3D11.h"
#include <string>
#include <vector>
#include <unordered_map>

struct Mesh;
class Shader;
class ShaderResource;
class ConstantBuffer;
class VertexBuffer;
class IndexBuffer;

typedef std::unordered_map<size_t, std::vector<size_t>> MeshTransformMap;

class Material
{
public:
	~Material();

	static Material* Create();

	void Render(ConstantBuffer*);
	void UpdateIfDirty();
	
	void SetShader(Shader* shader);
	
	void DeregisterMeshInfo(size_t meshIndex, size_t transformIndex);
	void RegisterMeshInfo(size_t meshIndex, size_t transformIndex);

private:
	bool Initialize();
	bool InitializeBuffers();

	Material();
	Material(const Material&) = delete;

	bool m_isDirty;
	Shader* m_shader;
	VertexBuffer* m_myVertexBuffer;
	IndexBuffer* m_myIndexBuffer;
	MeshTransformMap m_renderMap;
};
