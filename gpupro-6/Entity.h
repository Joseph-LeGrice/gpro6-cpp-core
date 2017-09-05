#pragma once

#include "Matrix.h"
#include "Vector3.h"
#include "Component.h"

#include <vector>
#include <typeindex>
#include <type_traits>
#include <unordered_map>

class SceneGraph;
typedef std::vector<Component*> ComponentList;
typedef std::unordered_map<std::type_index, ComponentList> ComponentMap;

class Entity
{
	friend SceneGraph;

public:
	static Entity& Instantiate();
	static void Destroy(Entity& e);

	// TODO: Add Child / Parent
	
	template<class T> T& AddComponent(); 
	template<class T> T& GetComponent();
	template<class T> ComponentList& GetComponents();
	ComponentList GetAllComponents();

	const Matrix4x4 GetTransformationMatrix();
	void SetTranslation(Vector3 position);
	//void SetRotation(Quaternion rot); //TODO: Quaternions
	void SetScale(Vector3 scale);

private:
	Matrix4x4 m_scale;
	Matrix4x4 m_rotation;
	Matrix4x4 m_translation;

	ComponentMap m_componentMap;

	Entity();
	~Entity();
	Entity(const Entity&) = delete;
};

template<class T>
T& Entity::AddComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "Type passed to AddComponent must be a Component.");

	T* c = new T();
	c->m_entity = this;
	if (!m_componentMap.count(typeid(c)))
	{
		m_componentMap[typeid(c)] = std::vector<Component*>();
	}
	m_componentMap[typeid(c)].push_back((Component*)c);
	GameSystem::SceneManager()->GetSceneGraph()->m_allComponents.push_back((Component*)c);

	return *c;
}

template<class T>
ComponentList& Entity::GetComponents()
{
	static_assert(std::is_base_of<Component, T>::value, "Type passed to GetComponents must be a Component.");
	
	if (m_componentMap->count(typeid(c)) && m_componentMap[typeid(c)].size() > 0)
	{
		return &m_componentMap[typeid(c)];
	}
	return nullptr;
}

template<class T>
T& Entity::GetComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "Type passed to GetComponent must be a Component.");

	std::vector<Component*> allComponents = GetComponents<T>();
	if (allComponents != nullptr)
	{
		return (T)allComponents[0];
	}
	return nullptr;
}
