#pragma once

#include "D3D11.h"
#include "Component.h"
#include "Material.h"


class Renderer : Component
{
public:
	Renderer();
	~Renderer();

	void SetMaterial(Material*);
	Material* GetMaterial();

private:
	Material* m_material;
};

