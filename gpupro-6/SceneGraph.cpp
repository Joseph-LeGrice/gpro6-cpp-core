#include "stdafx.h"

#include "SceneGraph.h"
#include "Entity.h"
#include "Component.h"
#include <algorithm>

SceneGraph::SceneGraph()
{
	m_rootEntities = std::vector<Entity*>();
	m_allComponents = std::vector<Component*>();
}

SceneGraph::~SceneGraph()
{
	for (size_t i = 0; i < m_rootEntities.size(); ++i)
	{
		DeleteEntity(*m_rootEntities[i]);
	}
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

void SceneGraph::RegisterEntity(Entity& e)
{
	m_rootEntities.push_back(&e);
}

void SceneGraph::DeleteEntity(Entity& e)
{
	ComponentList thisList = e.GetAllComponents();
	for (size_t i = 0; i < thisList.size(); ++i)
	{
		Component* thisComponent = thisList[i];
		DeleteComponent(*thisComponent);
	}
	delete &e;
}

void SceneGraph::RegisterComponent(Component& c)
{
	m_allComponents.push_back(&c);
}

void SceneGraph::DeleteComponent(Component& c)
{
	m_allComponents.erase(std::remove(m_allComponents.begin(), m_allComponents.end(), &c), m_allComponents.end());
	delete &c;
}
