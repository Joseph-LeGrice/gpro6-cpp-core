#include "stdafx.h"
#include "Entity.h"
#include "GameSystem.h"
#include "SceneManagementSystem.h"
#include "SceneGraph.h"

#include <algorithm>

Entity& Entity::Instantiate()
{
	Entity* e = new Entity();
	SceneManagementSystem::Instance()->GetSceneGraph()->RegisterEntity(*e);
	return *e;
}

void Entity::Destroy(Entity& e)
{
	SceneManagementSystem::Instance()->GetSceneGraph()->DeleteEntity(e);
}

Entity::Entity()
{
	m_componentMap = std::unordered_map<std::type_index, std::vector<Component*>>();
	m_scale = { 1.0f, 1.0f, 1.0f };
}

Entity::~Entity()
{
}

ComponentList Entity::GetAllComponents()
{
	ComponentList result = ComponentList();
	for (ComponentMap::iterator it = m_componentMap.begin(); it != m_componentMap.end(); ++it)
	{
		ComponentList thisList = it->second;
		result.insert(result.end(), thisList.begin(), thisList.end());
	}
	return result;
}

void Entity::SetTranslation(Vector3 position)
{
	m_position = position;
}

void Entity::SetRotation(Quaternion rot)
{
	m_rotation = rot;
}

void Entity::SetScale(Vector3 scale)
{
	m_scale = scale;
}

const Matrix4x4 Entity::GetTransformationMatrix()
{
	return m_position.GetTranslationMatrix() * m_scale.GetScaleMatrix() * m_rotation.GetMatrix();
}

Matrix4x4 Entity::GetTranslation()
{
	return m_position.GetTranslationMatrix();
}
