#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "D3D11.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(ID3D11Device* device);
	void Render(ID3D11DeviceContext* deviceContext);

protected:
	virtual Shader* InitShaders(ID3D11Device* device) = 0;
	virtual Mesh* InitMesh(ID3D11Device* device) = 0;

private:
	Mesh* m_mesh;
	Shader* m_shader;
};

