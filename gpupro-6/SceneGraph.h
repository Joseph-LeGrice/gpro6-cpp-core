#pragma once

#include <unordered_map>
#include <vector>

class Entity;
class Camera;
class Component;

typedef std::vector<Entity*> EntityList;
typedef std::vector<Component*> ComponentList; 

class SceneGraph
{
	friend Entity;
	friend Camera;

public:
	SceneGraph();
	~SceneGraph();

	Camera& GetCamera();
	void InitScene();
	void UpdateScene();
	void DeInitScene();

private:
	EntityList m_rootEntities;
	ComponentList m_allComponents;
	Camera* m_camera;

	void RegisterCamera(Camera& cam);
	void RegisterEntity(Entity& e); 
	void DeleteEntity(Entity& e);
	void RegisterComponent(Component& c);
	void DeleteComponent(Component& c);
};