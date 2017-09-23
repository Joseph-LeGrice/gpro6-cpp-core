#include "stdafx.h"

#include "SceneGraph.h"
#include "Entity.h"
#include "Component.h"
#include <algorithm>

SceneGraph::SceneGraph()
{
	m_rootEntities = std::vector<Entity*>();
}

SceneGraph::~SceneGraph()
{
	for (size_t i = 0; i < m_rootEntities.size(); ++i)
	{
		DeleteEntity(*m_rootEntities[i]);
	}

	for (auto it = m_componentMap.begin(); it != m_componentMap.end(); ++it)
	{
		for (auto compIt = it->second.begin(); compIt != it->second.end(); ++compIt)
		{
			delete &compIt;
		}
	}
}

Camera& SceneGraph::GetCamera()
{
	return *m_camera;
}

void SceneGraph::RegisterCamera(Camera& cam)
{
	m_camera = &cam;
}

void SceneGraph::RegisterEntity(Entity& e)
{
	m_rootEntities.push_back(&e);
}

void SceneGraph::DeleteEntity(Entity& e)
{
	delete &e;
}

