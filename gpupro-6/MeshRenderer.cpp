#include "stdafx.h"
#include "MeshRenderer.h"
#include "Mesh.h"


MeshRenderer::MeshRenderer()
{
	m_meshInfo = new MeshInfo();
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::SetMesh(Mesh* mesh)
{
	m_meshInfo->m_mesh = mesh;
}

void MeshRenderer::OnMaterialUpdated(Material* oldMaterial, Material* newMaterial)
{
	if (oldMaterial != nullptr)
	{
		oldMaterial->DeregisterMeshInfo(m_meshInfo);
	}
	newMaterial->RegisterMeshInfo(m_meshInfo);
}
