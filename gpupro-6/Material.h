#pragma once

#include "D3D11.h"
#include <string>
#include <vector>

class Mesh;
class Shader;
class ShaderResource;
class ConstantBuffer;

class Material
{
public:
	~Material();

	static Material* Create();

	void Render(ConstantBuffer*);
	
	void SetShader(Shader* shader);
	
	void DeregisterMeshInfo(size_t);
	Mesh* GetMeshInfo(size_t);
	size_t RegisterMeshInfo(Mesh&);

private:
	bool Initialize();
	bool InitializeBuffers();

	Material();
	Material(const Material&) = delete;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	Shader* m_shader;
	std::vector<Mesh> m_meshes;};

