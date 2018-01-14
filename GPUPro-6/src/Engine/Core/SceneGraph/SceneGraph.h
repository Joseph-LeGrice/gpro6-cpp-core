#pragma once

#include "Engine/Core/SceneGraph/SceneGraphDefinition.hpp"

#include "Engine/Core/Graphics/Components/Camera.h"
#include "Engine/Core/Graphics/Components/Transform.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"
#include "Engine/Core/Graphics/Components/Light.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Extra/TransformSync/TranslationSync.h"

typedef SceneGraphDefinition<
    TransformComponent,
    CameraComponent,
    MeshRendererComponent,
    EntityComponent,
    LightComponent,
    TranslationSyncComponent
> SceneGraph;

void InitSceneGraph();
SceneGraph& GetSceneGraph();
void DestroySceneGraph();
