#pragma once

#include <unordered_map>
#include <vector>

class Entity;
class Component;

typedef std::vector<Entity*> EntityList;
typedef std::vector<Component*> ComponentList; 

class SceneGraph
{
	friend Entity;

public:
	SceneGraph();
	~SceneGraph();

	void InitializeScene();
	void UpdateScene();
	void DestroyScene();

private:
	EntityList m_rootEntities;
	ComponentList m_allComponents;
};