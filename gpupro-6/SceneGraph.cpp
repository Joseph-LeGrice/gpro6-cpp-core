#include "stdafx.h"

#include "SceneGraph.h"
#include "Entity.h"
#include "Component.h"

SceneGraph::SceneGraph()
{
	m_rootEntities = std::vector<Entity*>();
	m_allComponents = std::vector<Component*>();
}

SceneGraph::~SceneGraph()
{
	for (size_t i = 0; i < m_rootEntities.size(); i++)
	{
		SAFE_DELETE(m_rootEntities[i]);
	}
	m_rootEntities.clear();
}

void SceneGraph::InitializeScene()
{
	for (size_t i=0; i<m_allComponents.size(); i++)
	{
		m_allComponents[i]->Init();
	}
}

void SceneGraph::UpdateScene()
{
	for (size_t i = 0; i < m_allComponents.size(); i++)
	{
		m_allComponents[i]->Tick();
	}
}

void SceneGraph::DestroyScene()
{
	for (size_t i = 0; i < m_allComponents.size(); i++)
	{
		m_allComponents[i]->DeInit();
	}
}

//
//void SceneGraph::RebuildComponentMap() //TODO: Speed up!
//{
//	m_componentMap.clear();
//	for each (Entity* e in m_rootEntities)
//	{
//		for each (Component* c in *e->GetAllComponents())
//		{
//			if (!m_componentMap.count(typeid(c)))
//			{
//				m_componentMap[typeid(c)] = std::vector<Component*>();
//			}
//			m_componentMap[typeid(c)].push_back(c);
//		}
//	}
//}
