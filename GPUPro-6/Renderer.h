#pragma once

#include "D3D11.h"
#include "Component.h"
#include "Material.h"


class Renderer : public Component
{
public:
	Renderer();

	void SetMaterial(Material*);
	Material* GetMaterial();

protected:
	virtual void OnMaterialUpdated(Material* oldMaterial, Material* newMaterial) = 0;

private:
	Material* m_material;
};

