#include "stdafx.h"
#include "MaterialManagementSystem.h"


MaterialManagementSystem::MaterialManagementSystem()
{
	m_instancedMaterials = std::vector<Material*>();
}


MaterialManagementSystem::~MaterialManagementSystem()
{
	for each (Material* m in m_instancedMaterials)
	{
		SAFE_DELETE(m);
	}
}

const std::vector<Material*>* MaterialManagementSystem::GetAllMaterials()
{
	return &m_instancedMaterials;
}

const void MaterialManagementSystem::RegisterInstancedMaterial(Material* m)
{
	m_instancedMaterials.push_back(m);
}
