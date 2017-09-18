#pragma once
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

