#pragma once

#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/Entity.h"

#include "DataStructures/ComponentArray.h"
#include <vector>

struct SceneGraph
{
	ComponentArray<Camera> m_cameras;
	ComponentArray<Transform> m_transforms;
	
    //ComponentArray<Entity> m_entities;
    std::vector<Entity> m_entities;

    SceneGraph() = default;
    ~SceneGraph() = default;
    SceneGraph(SceneGraph&) = delete;
};
