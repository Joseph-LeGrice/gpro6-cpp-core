#pragma once

#include "SceneGraph.hpp"

class SceneGraphManager
{
public:
	SceneGraphManager(SceneGraph& scene) : m_currentScene(scene) { }
	~SceneGraphManager() = default;

	SceneGraph& GetCurrentScene();

private:
	SceneGraph& m_currentScene;
};