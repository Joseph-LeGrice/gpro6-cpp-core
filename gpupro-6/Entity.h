#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Component.h"
#include "Quaternion.h"

#include <vector>
#include <typeindex>
#include <type_traits>
#include <unordered_map>

class SceneGraph;
typedef std::vector<size_t> IndexList;
typedef std::unordered_map<std::type_index, IndexList> IndexMap;

struct Transform
{
	// TODO: Child / Parent functionality
	
	Vector4 m_position;
	Vector4 m_scale;
	Quaternion m_rotation;

	Transform()
	{
		m_scale = { 1.0f, 1.0f, 1.0f };
	}

	Matrix4x4 GetTransformationMatrix()
	{
		return m_position.GetTranslationMatrix() * m_scale.GetScaleMatrix() * m_rotation.GetMatrix();
	}
};

class Entity
{
	friend SceneGraph;

public:
	static Entity& Instantiate();
	static void Destroy(Entity& e);

	template<class T> T& AddComponent();
	template<class T> void RemoveComponent();
	IndexList GetIndicesForComponent(std::type_index);
	
	Transform& GetTransform();

private:
	Transform m_transform;
	IndexMap m_componentIndexMap;

	Entity();
	~Entity();
	Entity(const Entity&) = delete;
};

template<class T>
T& Entity::AddComponent()
{
	size_t index = SceneManagementSystem::Instance()->GetSceneGraph()->AddComponent<T>();
	m_componentIndexMap[typeid(T)].push_back(index);
	return *SceneManagementSystem::Instance()->GetSceneGraph()->GetComponent<T>(index);
}

template<class T>
void Entity::RemoveComponent()
{
	//SceneManagementSystem::Instance()->GetSceneGraph()->Remo<T>(index);
}
