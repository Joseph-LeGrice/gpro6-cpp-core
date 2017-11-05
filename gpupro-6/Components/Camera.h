#pragma once

#include "Components/ComponentType.hpp"
#include "DataStructures/Matrix4x4.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/GraphicsSystem.h"

struct Camera
{
	size_t m_transformIndex;
	Matrix4x4 m_projectionMatrix;
};

Camera CameraSetOrthographic(float size, float depth, float aspectRatio);
Camera CameraSetPerspective(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar);

struct InitCamera
{
    Camera operator()()
    {
        float viewportWidth = SystemManager::GetSystem<GraphicsSystem>()->GetViewportWidth();
        float viewportHeight = SystemManager::GetSystem<GraphicsSystem>()->GetViewportHeight();
        float aspectRatio = viewportWidth / viewportHeight;

        float screenNear = 0.1f;
        float screenDepth = 100.0f;
        float fieldOfView = (float)D3DX_PI / 2.0f;

        return CameraSetPerspective(fieldOfView, aspectRatio, screenNear, screenDepth);
    }
};

typedef ComponentRegistrationInfo<Camera, 1, InitCamera> CameraComponent;
