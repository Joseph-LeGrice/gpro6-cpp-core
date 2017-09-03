#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
	m_material = nullptr;
}

void Renderer::SetMaterial(Material* mat)
{
	this->OnMaterialUpdated(m_material, mat);
	m_material = mat;
}

Material* Renderer::GetMaterial()
{
	return m_material;
}

