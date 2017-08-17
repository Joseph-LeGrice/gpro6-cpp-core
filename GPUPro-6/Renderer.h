#pragma once

#include "D3D11.h"
#include "Material.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	virtual bool Initialize(ID3D11Device* device) = 0;
	virtual void Render(ID3D11DeviceContext* deviceContext) = 0;

	void SetMaterial(const Material&);
	const Material* GetMaterial();

private:
	const Material* m_material;
};

