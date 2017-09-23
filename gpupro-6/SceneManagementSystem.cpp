#include "stdafx.h"
#include "SceneManagementSystem.h"
#include "SceneGraph.h"

SceneManagementSystem::SceneManagementSystem()
{
	m_sceneGraph = new SceneGraph();
}


SceneManagementSystem::~SceneManagementSystem()
{
	SAFE_DELETE(m_sceneGraph);
}

void SceneManagementSystem::VariableTick()
{
}

SceneGraph* SceneManagementSystem::GetSceneGraph()
{
	return m_sceneGraph;
}
