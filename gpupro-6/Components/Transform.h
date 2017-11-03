#pragma once

#include "DataStructures\Vector3.h"
#include "DataStructures\Quaternion.h"

struct Matrix4x4;

struct Transform
{
	// TODO: Child / Parent functionality
    int m_entityIndex;
	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;
};

Transform TransformNew();
Matrix4x4 TransformGetMatrix(const Transform& t);
Matrix4x4 TransformGetCameraViewMatrix(const Transform& t);
