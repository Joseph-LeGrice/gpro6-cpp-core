#pragma once

#include <vector>
#include "Material.h"

class MaterialManagementSystem
{
public:
	MaterialManagementSystem();
	~MaterialManagementSystem();

	const std::vector<Material*>* GetAllMaterials();
	const void RegisterInstancedMaterial(Material&);

private:
	std::vector<Material*> m_instancedMaterials;
};

