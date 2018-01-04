#pragma once

#include "SystemManagerDefinition.hpp"

#include "Core/Graphics/GraphicsSystem.h"
#include "Core/Graphics/LightingSystem.h"
#include "Core/Input/InputSystem.h"
#include "Extra/Locomotion/NoClipLocomotion.h"

typedef SystemManagerDefinition<
    GraphicsSystem,
    LightingSystem,
    InputSystem,
    NoClipLocomotion
> SystemManager;

void InitSystemManager();
SystemManager& GetSystemManager();
void DestroySystemManager();