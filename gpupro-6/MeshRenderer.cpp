#include "stdafx.h"

#include "Entity.h"
#include "Component.h"
#include "MeshRenderer.h"


MeshRenderer::MeshRenderer()
{
	m_meshIndex = -1;
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::SetMesh(Mesh mesh)
{
	Material* currentMat = GetMaterial();
	if (currentMat != nullptr)
	{
		if (m_meshIndex > -1)
		{
			currentMat->DeregisterMeshInfo(m_meshIndex);
		}
		m_meshIndex = currentMat->RegisterMeshInfo(mesh);
	}
}

void MeshRenderer::OnMaterialUpdated(Material* oldMaterial, Material* newMaterial)
{
	if (oldMaterial != nullptr && m_meshIndex > -1)
	{
		Mesh* m = oldMaterial->GetMeshInfo(m_meshIndex);
		size_t newIndex = newMaterial->RegisterMeshInfo(*m);

		oldMaterial->DeregisterMeshInfo(m_meshIndex);
		m_meshIndex = newIndex;
	}
}
