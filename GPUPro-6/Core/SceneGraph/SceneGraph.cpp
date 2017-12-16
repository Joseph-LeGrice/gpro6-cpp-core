#include "stdafx.h"
#include "SceneGraph.h"


SceneGraph& GetSceneGraph()
{
    static SceneGraph* s_sceneGraph = new SceneGraph();
    return *s_sceneGraph;
}
