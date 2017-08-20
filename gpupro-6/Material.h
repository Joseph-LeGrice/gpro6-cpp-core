#pragma once

#include "D3D11.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"

class Material
{
public:
	~Material();

	static Material* Create();

	void Render();
	void RegisterMesh(Mesh* mesh);
	void CompileShader(std::wstring shaderFilename);

private:
	bool Initialize();
	bool InitializeBuffers();

	Material();

	std::vector<Mesh*>* m_meshes;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	ConstantBuffer* m_constBuffer;
	Shader* m_shader;
};

