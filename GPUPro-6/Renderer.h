#pragma once

#include "D3D11.h"
#include "Component.h"
#include "Material.h"


class Renderer : Component
{
public:
	Renderer();
	~Renderer();

	void SetMaterial(const Material&);
	const Material* GetMaterial();

private:
	const Material* m_material;
};

