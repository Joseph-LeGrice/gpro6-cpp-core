#include "stdafx.h"
#include "SceneGraph.h"
#include "Entity.h"

SceneGraph::SceneGraph()
{
	m_componentMap = std::unordered_map<std::type_index, std::vector<Component*>>();
	m_rootEntities = std::vector<Entity*>();
}

SceneGraph::~SceneGraph()
{
}


void SceneGraph::AddRootEntity(Entity* newEntity)
{
	m_rootEntities.push_back(newEntity);
	RebuildComponentMap();
}


void SceneGraph::RebuildComponentMap() //TODO: Speed up!
{
	m_componentMap.clear();
	for each (Entity* e in m_rootEntities)
	{
		for each (Component* c in *e->GetAllComponents())
		{
			if (!m_componentMap.count(typeid(c)))
			{
				m_componentMap[typeid(c)] = std::vector<Component*>();
			}
			m_componentMap[typeid(c)].push_back(c);
		}
	}
}
