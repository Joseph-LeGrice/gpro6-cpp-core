#pragma once

#include "D3D11.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "ResourceViews.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(ID3D11Device* device);
	void Render(ID3D11DeviceContext* deviceContext);

	ConstantBuffer* GetConstantBuffer();

protected:
	virtual Mesh* InitMesh(ID3D11Device* device) = 0;
	virtual Shader* InitShaders(ID3D11Device* device) = 0;
	virtual ResourceViews* InitResourceViews(ID3D11Device* device) = 0;
	virtual ConstantBuffer* InitConstantBuffer(ID3D11Device* device) = 0;

private:
	Mesh* m_mesh;
	Shader* m_shader;
	ResourceViews* m_resources;
	ConstantBuffer* m_constBuffer;
};

