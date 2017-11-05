#pragma once

#include "Components/ComponentType.hpp"
#include "DataStructures\Vector3.h"
#include "DataStructures\Quaternion.h"

struct Matrix4x4;

struct Transform
{
    // TODO: Child / Parent functionality
    Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;
};

const struct InitTransform
{
    Transform operator()()
    {
        Transform t;
        t.m_scale = { 1.0f, 1.0f, 1.0f };
        t.m_position = { 0.0f, 0.0f, 0.0f };
        t.m_rotation = QuaternionIdentity();
        return t;
    }
};

Matrix4x4 TransformGetMatrix(const Transform& t);
Matrix4x4 TransformGetCameraViewMatrix(const Transform& t);

typedef ComponentRegistrationInfo<Transform, 1, InitTransform> TransformComponent;
