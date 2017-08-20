#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetMaterial(Material* mat)
{
	m_material = mat;
}

Material* Renderer::GetMaterial()
{
	return m_material;
}

