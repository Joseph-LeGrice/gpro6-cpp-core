#pragma once

#include "Engine/Core/SceneGraph/Components/Util/ComponentType.hpp"
#include "MyMath/Matrix/Matrix4x4.h"
#include "Engine/Core/SystemManagement/SystemManager.h"
#include "Engine/Core/Graphics/GraphicsSystem.h"
#include "MyMath/MathDefines.h"

struct Camera
{
    Matrix4x4 m_projectionMatrix;
    //TODO: Add reference field for skybox?

    static Camera CreateOrthographic(float size, float depth, float aspectRatio);
    static Camera CreatePerspective(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar);
};

namespace CameraInternal
{
    struct InitCamera
    {
        Camera operator()()
        {
            float viewportWidth = GetSystemManager().GetSystem<GraphicsSystem>()->GetViewportWidth();
            float viewportHeight = GetSystemManager().GetSystem<GraphicsSystem>()->GetViewportHeight();
            float aspectRatio = viewportWidth / viewportHeight;

            float screenNear = 0.1f;
            float screenDepth = 100.0f;
            float fieldOfView = 60.0f * MyMath::DegToRad;

            return Camera::CreatePerspective(fieldOfView, aspectRatio, screenNear, screenDepth);
        }
    };
}

typedef ComponentRegistrationInfo<Camera, 2, CameraInternal::InitCamera> CameraComponent;
