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
	m_vertexBuffer.SetCurrentIfValid();
	m_indexBuffer.SetCurrentIfValid();
}

void MeshManager::RegisterMesh(Mesh* m)
{
	size_t resourceIndex = m->GetResourceIndex();
	if (m_meshInfoMapping.count(resourceIndex) == 0) {
		m_meshInfoMapping.insert({ resourceIndex, {} });
		RefreshBuffers();
	}
}

void MeshManager::UnregisterMesh(Mesh* m)
{
	size_t resourceIndex = m->GetResourceIndex();
	if (m_meshInfoMapping.count(resourceIndex) != 0) {
		m_meshInfoMapping.erase(m_meshInfoMapping.find(resourceIndex));
		RefreshBuffers();
	}
}

MeshInfo MeshManager::GetMapping(Mesh* m)
{
	size_t resourceIndex = m->GetResourceIndex();
	custom_assert::is_true(m_meshInfoMapping.count(resourceIndex) != 0, "No mapping exists for Mesh!");
	return m_meshInfoMapping[resourceIndex];
}

void MeshManager::RefreshBuffers()
{
	std::vector<VertexData> verts;
	std::vector<uint16_t> indices;

	for (std::unordered_map<size_t, MeshInfo>::iterator it = m_meshInfoMapping.begin();
		it != m_meshInfoMapping.end(); it++)
	{
		Mesh* m = m_resourceManager.GetAsset<Mesh>(it->first);

		size_t indexStart = indices.size(); 
		size_t vertStart = verts.size();
		
		verts.insert(verts.end(), m->GetVertexData().begin(), m->GetVertexData().end());
		indices.insert(indices.end(), m->GetIndices().begin(), m->GetIndices().end());

		size_t numIndices = indices.size() - indexStart;
		size_t numVerts = verts.size() - vertStart;

		it->second = { indexStart, vertStart, numIndices, numVerts };
	}
}
