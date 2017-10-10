#pragma once

#include <vector>
#include "Graphics\Material.h"
#include "Systems\GameSystem.h"

class MaterialManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(MaterialManagementSystem)

public:
	const std::vector<Material*>* GetAllMaterials();
	const void RegisterInstancedMaterial(Material&);

private:
	std::vector<Material*> m_instancedMaterials;
};

