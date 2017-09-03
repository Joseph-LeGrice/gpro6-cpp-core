#include "stdafx.h"
#include "Entity.h"
#include "GameSystem.h"
#include "SceneManagementSystem.h"
#include "SceneGraph.h"

#include <algorithm>

Entity::Entity()
{
	Matrix4x4::MatrixIdentity(&m_translation);
	Matrix4x4::MatrixIdentity(&m_scale);
	Matrix4x4::MatrixIdentity(&m_rotation);

	m_componentMap = std::unordered_map<std::type_index, std::vector<Component*>>();
}

Entity::~Entity()
{
	SceneGraph* currentSceneGraph = GameSystem::SceneManager()->GetSceneGraph();
	ComponentList currentSceneGraphComponents = currentSceneGraph->m_allComponents;
	for (ComponentMap::iterator it = m_componentMap.begin(); it != m_componentMap.end(); ++it)
	{
		ComponentList thisList = it->second;
		for (size_t i = 0; i < thisList.size(); ++i)
		{
			Component* thisComponent = thisList[i];
			currentSceneGraphComponents.erase(std::remove(currentSceneGraphComponents.begin(), currentSceneGraphComponents.end(), thisComponent), currentSceneGraphComponents.end());
			SAFE_DELETE(thisComponent);
		}
	}
	m_componentMap.clear();
}

Entity& Entity::Instantiate()
{
	Entity* e = new Entity();
	GameSystem::SceneManager()->GetSceneGraph()->m_rootEntities.push_back(e);
	return *e;
}

void Entity::SetTranslation(Vector3 position)
{
	m_translation.M41 = position.X;
	m_translation.M42 = position.Y;
	m_translation.M43 = position.Z;
}


void Entity::SetScale(Vector3 scale)
{
	m_scale.M11 = scale.X;
	m_scale.M22 = scale.Y;
	m_scale.M33 = scale.Z;
}

const Matrix4x4 Entity::GetTransformationMatrix()
{
	return m_translation * m_scale * m_rotation;
}
