#include "stdafx.h"
#include "MeshRenderer.h"
#include "Mesh.h"


MeshRenderer::MeshRenderer()
{
	m_meshInfo = new MeshInfo();
	Matrix4x4::MatrixIdentity(&m_meshInfo->m_transform);

	m_meshInfo->m_transform.M41 = 0.0f;
	m_meshInfo->m_transform.M42 = 0.0f;
	m_meshInfo->m_transform.M43 = 5.0f;
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
