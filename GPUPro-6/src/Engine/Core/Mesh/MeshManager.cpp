#include "stdafx.h"
#include "MeshManager.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Engine/Core/Graphics/Buffers/IndexBuffer.h"
#include "Engine/Core/Graphics/Buffers/VertexBuffer.h"

MeshManager::~MeshManager()
{
}

void MeshManager::BindBuffers()
{
	m_vertexBuffer->SetCurrentIfValid();
	m_indexBuffer->SetCurrentIfValid();
}

void MeshManager::RegisterMesh(Mesh* m)
{
	int resourceId = m->GetResourceID();
	if (m_meshInfoMapping.count(resourceId) == 0) {
		m_meshInfoMapping.insert({ resourceId, {} });
		RefreshBuffers();
	}
}

void MeshManager::UnregisterMesh(Mesh* m)
{
	int resourceId = m->GetResourceID();
	if (m_meshInfoMapping.count(resourceId) != 0) {
		m_meshInfoMapping.erase(m_meshInfoMapping.find(resourceId));
		RefreshBuffers();
	}
}

MeshInfo MeshManager::GetMapping(Mesh* m)
{
	int resourceId = m->GetResourceID();
	custom_assert::is_true(m_meshInfoMapping.count(resourceId) != 0, "No mapping exists for Mesh!");
	return m_meshInfoMapping[resourceId];
}

void MeshManager::RefreshBuffers()
{
	std::vector<VertexData> verts;
	std::vector<uint16_t> indices;

	for (std::unordered_map<int, MeshInfo>::iterator it = m_meshInfoMapping.begin();
		it != m_meshInfoMapping.end(); it++)
	{
		Mesh* m = GetResourceManager().GetAsset<Mesh>(it->first);

		size_t indexStart = indices.size(); 
		size_t vertStart = verts.size();
		
		verts.insert(verts.end(), m->GetVertexData().begin(), m->GetVertexData().end());
		indices.insert(indices.end(), m->GetIndices().begin(), m->GetIndices().end());

		size_t numIndices = indices.size() - indexStart;
		size_t numVerts = verts.size() - vertStart;

		it->second = { indexStart, vertStart, numIndices, numVerts };
	}
}
