#pragma once
#include "Systems\GameSystem.h"
#include "DataStructures\SceneGraph.h"

class SceneManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(SceneManagementSystem);

public:
	virtual void VariableTick() override;
	SceneGraph* GetSceneGraph();
	
private:
	SceneGraph* m_sceneGraph;
};

