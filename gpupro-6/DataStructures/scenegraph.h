#pragma once

#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/Entity.h"

#include "DataStructures/ComponentArray.h"

struct SceneGraph
{
	ComponentArray<Camera> m_cameras;
	ComponentArray<Transform> m_transforms;
	//ComponentArray<Entity> m_entities;

    SceneGraph() = default;
    ~SceneGraph() = default;
    SceneGraph(SceneGraph&) = delete;
};
