#pragma once
#include "Renderer.h"
class MeshRenderer :
	public Renderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	virtual bool Initialize(ID3D11Device* device) override;
	virtual void Render(ID3D11DeviceContext* deviceContext) override;

private:
	Mesh* m_mesh;
	Shader* m_shader;
};

