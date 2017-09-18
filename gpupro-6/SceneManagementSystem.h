#pragma once
#include "GameSystem.h"
#include "ISystem.h"

class SceneGraph;

class SceneManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(SceneManagementSystem)
public:
	SceneGraph* GetSceneGraph();
	
private:
	SceneGraph* m_sceneGraph;
};

