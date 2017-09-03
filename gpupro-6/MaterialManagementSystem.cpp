#include "stdafx.h"
#include "MaterialManagementSystem.h"


MaterialManagementSystem::MaterialManagementSystem()
{
	m_instancedMaterials = std::vector<Material*>();
}


MaterialManagementSystem::~MaterialManagementSystem()
{
	SAFE_DELETE_VECTOR_STACK(m_instancedMaterials);
}

const std::vector<Material*>* MaterialManagementSystem::GetAllMaterials()
{
	return &m_instancedMaterials;
}

const void MaterialManagementSystem::RegisterInstancedMaterial(Material& m)
{
	m_instancedMaterials.push_back(&m);
}
