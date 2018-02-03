#pragma once

#include "SystemManagerDefinition.hpp"

#include "Engine/Core/Graphics/GraphicsSystem.h"
#include "Engine/Core/Graphics/LightingSystem.h"
#include "Engine/Core/Input/InputSystem.h"
#include "Engine/Extra/Locomotion/NoClipLocomotion.h"
#include "Engine/Extra/MarchingCubes/MarchingSquaresSystem.h"

typedef SystemManagerDefinition<
    GraphicsSystem,
    LightingSystem,
    InputSystem,
    NoClipLocomotion,
    MarchingSquaresSystem
> SystemManager;

void InitSystemManager();
SystemManager& GetSystemManager();
void DestroySystemManager();