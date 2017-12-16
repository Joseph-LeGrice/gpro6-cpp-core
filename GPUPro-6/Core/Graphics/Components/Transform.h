#pragma once

#include "Core/SceneGraph/Components/Util/ComponentType.hpp"
#include "Core/DataStructures\Vector3.h"
#include "Core/DataStructures\Quaternion.h"

struct Matrix4x4;

struct Transform
{
    // TODO: Child / Parent functionality
    Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;

    static Matrix4x4 GetMatrix(const Transform& t);
    static Matrix4x4 GetCameraViewMatrix(const Transform& t);
};

namespace TransformInternal
{
    struct InitTransform
    {
        Transform operator()()
        {
            Transform t;
            t.m_scale = { 1.0f, 1.0f, 1.0f };
            t.m_position = { 0.0f, 0.0f, 0.0f };
            t.m_rotation = Quaternion::Identity();
            return t;
        }
    };
}

typedef ComponentRegistrationInfo<Transform, 1, TransformInternal::InitTransform> TransformComponent;
