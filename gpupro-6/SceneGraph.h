#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <type_traits>

class Entity;
class Camera;
class Component;

typedef std::vector<Entity*> EntityList;

typedef std::vector<Component> ComponentRefList; 
typedef std::unordered_map<std::type_index, ComponentRefList> ComponentRefMap;

class SceneGraph
{
	friend Entity;
	friend Camera;

public:
	SceneGraph();
	~SceneGraph();

	Camera& GetCamera();

	template<class T> size_t AddComponent();
	//template<class T> void RemoveComponent(size_t);
	template<class T> T* GetComponent(size_t);
	template<class T> ComponentRefList* GetComponents();

private:
	ComponentRefMap m_componentMap;

	EntityList m_rootEntities;
	Camera* m_camera;

	void RegisterCamera(Camera& cam);
	void RegisterEntity(Entity& e); 
	void DeleteEntity(Entity& e);
};


template<class T>
size_t SceneGraph::AddComponent()
{
	std::type_index ti = std::type_index(typeid(T));
	if (!m_componentMap.count(ti))
	{
		m_componentMap[ti] = std::vector<Component>();
	}

	size_t index = m_componentMap[ti].size();
	
	T c = T();
	m_componentMap[ti].push_back(c);

	return index;
}

template<class T>
ComponentRefList* SceneGraph::GetComponents()
{
	static_assert(std::is_base_of<Component, T>::value, "Type passed to GetComponents must be a Component.");

	std::type_index ti = std::type_index(typeid(T));
	if (m_componentMap.count(ti) && m_componentMap[ti].size() > 0)
	{
		return &m_componentMap[ti];
	}
	return nullptr;
}

template<class T>
T* SceneGraph::GetComponent(size_t index)
{
	static_assert(std::is_base_of<Component, T>::value, "Type passed to GetComponent must be a Component.");

	ComponentRefList* allComponents = GetComponents<T>();
	if (allComponents != nullptr)
	{
		return (T*)&allComponents[0];
	}
	return nullptr;
}
