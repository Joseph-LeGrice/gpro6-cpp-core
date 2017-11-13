#pragma once

#include "Components/Util/ComponentType.hpp"
#include "DataStructures/Matrix4x4.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/GraphicsSystem.h"

struct Camera
{
    Matrix4x4 m_projectionMatrix;

    static Camera CreateOrthographic(float size, float depth, float aspectRatio);
    static Camera CreatePerspective(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar);
};

namespace CameraInternal
{
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

            return Camera::CreatePerspective(fieldOfView, aspectRatio, screenNear, screenDepth);
        }
    };
}

typedef ComponentRegistrationInfo<Camera, 2, CameraInternal::InitCamera> CameraComponent;
