#pragma once

#include "Component.h"

#include <typeindex>
#include <unordered_map>
#include <vector>

class Entity;

class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();

	void AddRootEntity(Entity* newEntity);

private:
	void RebuildComponentMap();
	std::unordered_map<std::type_index, std::vector<Component*>> m_componentMap;
	std::vector<Entity*> m_rootEntities;
};