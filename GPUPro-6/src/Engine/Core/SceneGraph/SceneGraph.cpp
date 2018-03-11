#include "stdafx.h"
#include "SceneGraph.h"

SceneGraph* g_sceneGraph;

void InitSceneGraph()
{
	g_sceneGraph = new SceneGraph();
}

SceneGraph& GetSceneGraph()
{
	return *g_sceneGraph;
}

void DestroySceneGraph()
{
	delete g_sceneGraph;
}