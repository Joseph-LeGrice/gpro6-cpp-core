#pragma once
#include "ISystem.h"

class SceneGraph;

class SceneManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(SceneManagementSystem);

public:
	virtual void VariableTick() override;
	SceneGraph* GetSceneGraph();
	
private:
	SceneGraph* m_sceneGraph;
};

