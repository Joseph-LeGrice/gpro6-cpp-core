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

	void InitScene();
	void UpdateScene();
	void DeInitScene();

private:
	EntityList m_rootEntities;
	ComponentList m_allComponents;

	void RegisterEntity(Entity& e); 
	void DeleteEntity(Entity& e);
	void RegisterComponent(Component& c);
	void DeleteComponent(Component& c);
};