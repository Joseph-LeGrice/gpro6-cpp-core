#pragma once

#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/MeshRenderer.h"
#include "Components/Light.h"
#include "Components/Entity.h"

#include "DataStructures/ComponentArray.hpp"
#include <vector>

struct SceneGraph
{
    ComponentArray<TransformComponent> m_transforms;
    ComponentArray<CameraComponent> m_cameras;
    ComponentArray<LightComponent> m_lights;
    ComponentArray<MeshRendererComponent> m_meshRenderers;
    ComponentArray<Entity> m_entities;

    SceneGraph() = default;
    ~SceneGraph() = default;
    SceneGraph(SceneGraph&) = delete;
};
