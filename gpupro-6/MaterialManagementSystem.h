#pragma once

#include <vector>

typedef class Material;

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

