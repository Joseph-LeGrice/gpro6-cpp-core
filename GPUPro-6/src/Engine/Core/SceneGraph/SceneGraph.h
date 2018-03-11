#pragma once

#include "Engine/Core/SceneGraph/SceneGraphDefinition.hpp"

#include "Engine/Core/Graphics/Components/Camera.h"
#include "Engine/Core/Graphics/Components/Transform.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"
#include "Engine/Core/Graphics/Components/Light.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"


//TODO Rewrite for runtime adding of new types
typedef SceneGraphDefinition<
    TransformComponent,
    CameraComponent,
    MeshRendererComponent,
    EntityComponent,
    LightComponent
> SceneGraph;

void InitSceneGraph();
void DestroySceneGraph();
