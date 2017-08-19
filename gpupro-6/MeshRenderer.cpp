#include "stdafx.h"
#include "MeshRenderer.h"


MeshRenderer::MeshRenderer()
{
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::SetMesh(Mesh* mesh)
{
	m_mesh = mesh;
}
