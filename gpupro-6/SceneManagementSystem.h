#pragma once

class SceneGraph;

class SceneManagementSystem
{
public:
	SceneManagementSystem();
	~SceneManagementSystem();

	SceneGraph* GetSceneGraph();
	
private:
	SceneGraph* m_sceneGraph;
};

