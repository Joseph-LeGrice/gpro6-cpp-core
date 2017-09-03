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
	SAFE_DELETE_VECTOR_STACK(m_rootEntities);
}

void SceneGraph::InitScene()
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

void SceneGraph::DeInitScene()
{
	for (size_t i = 0; i < m_allComponents.size(); i++)
	{
		m_allComponents[i]->DeInit();
	}
}
