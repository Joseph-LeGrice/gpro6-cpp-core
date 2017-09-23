#include "stdafx.h"
#include "Entity.h"
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

IndexList Entity::GetIndicesForComponent(std::type_index ti)
{
	if (m_componentIndexMap.count(ti))
	{
		return m_componentIndexMap[ti];
	}
	else
	{
		return std::vector<size_t>();
	}
}

Transform& Entity::GetTransform()
{
	return m_transform;
}

Entity::Entity()
{

}

Entity::~Entity()
{
}
