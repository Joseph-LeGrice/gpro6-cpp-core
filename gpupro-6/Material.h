#pragma once

#include "D3D11.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"

class Material
{
public:
	Material();
	~Material();

	bool Initialize(ID3D11Device* device);
	void Render(ID3D11DeviceContext* deviceContext);
	void RegisterMesh(Mesh* mesh);

private:
	bool InitializeBuffers(ID3D11Device* device);
	bool CompileShader(ID3D11Device* device);

	std::vector<Mesh*>* m_meshes;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	ConstantBuffer* m_constBuffer;
	Shader* m_shader;
};

