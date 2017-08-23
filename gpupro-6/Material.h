#pragma once

#include "D3D11.h"

class Mesh;
class Shader;
class ConstantBuffer;

class Material
{
public:
	~Material();

	static Material* Create();

	void Render(ConstantBuffer*);
	void RegisterMeshInfo(MeshInfo mesh);
	void CompileShader(std::wstring shaderFilename);

private:
	bool Initialize();
	bool InitializeBuffers();

	Material();

	std::vector<MeshInfo>* m_meshes;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	Shader* m_shader;
};

