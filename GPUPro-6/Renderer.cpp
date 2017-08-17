#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetMaterial(const Material& mat)
{
	m_material = &mat;
}

const Material* Renderer::GetMaterial()
{
	return m_material;
}

