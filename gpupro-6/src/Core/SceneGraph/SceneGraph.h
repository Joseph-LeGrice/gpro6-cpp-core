#pragma once

#include "Core/SceneGraph/SceneGraphDefinition.hpp"

#include "Core/Graphics/Components/Camera.h"
#include "Core/Graphics/Components/Transform.h"
#include "Core/Graphics/Components/MeshRenderer.h"
#include "Core/Graphics/Components/Light.h"
#include "Core/SceneGraph/Components/Entity.h"
#include "Extra/TransformSync/TranslationSync.h"

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
