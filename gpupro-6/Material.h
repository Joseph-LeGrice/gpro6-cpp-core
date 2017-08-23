#pragma once

#include "D3D11.h"
#include <string>
#include <vector>

class Mesh;
class Shader;
class ConstantBuffer;
struct MeshInfo;

class Material
{
public:
	~Material();

	static Material* Create();

	void Render(ConstantBuffer*);
	void DeregisterMeshInfo(MeshInfo* mesh);
	void RegisterMeshInfo(MeshInfo* mesh);
	void CompileShader(std::wstring shaderFilename);

private:
	bool Initialize();
	bool InitializeBuffers();

	Material();

	std::vector<MeshInfo*>* m_meshes;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	Shader* m_shader;
};

