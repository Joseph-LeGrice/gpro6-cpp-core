#include "stdafx.h"

#include "Entity.h"
#include "Component.h"
#include "MeshRenderer.h"


MeshRenderer::MeshRenderer()
{
	m_meshInfo = MeshInfo();
	Matrix4x4::Identity(m_meshInfo.m_transform);
}

MeshRenderer::~MeshRenderer()
{
	SAFE_DELETE(m_meshInfo.m_mesh);
}

void MeshRenderer::Tick()
{
	m_meshInfo.m_transform = GetEntity().GetTransformationMatrix();
}

void MeshRenderer::SetMesh(Mesh& mesh)
{
	m_meshInfo.m_mesh = &mesh;
}

void MeshRenderer::OnMaterialUpdated(Material* oldMaterial, Material* newMaterial)
{
	if (oldMaterial != nullptr)
	{
		oldMaterial->DeregisterMeshInfo(m_meshInfo);
	}
	newMaterial->RegisterMeshInfo(m_meshInfo);
}
