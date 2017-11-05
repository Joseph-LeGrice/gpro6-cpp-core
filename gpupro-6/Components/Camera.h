#pragma once

#include "Components/ComponentType.hpp"
#include "DataStructures/Matrix4x4.h"

struct Camera
{
	size_t m_transformIndex;
	Matrix4x4 m_projectionMatrix;
};

Camera CameraTestNew();
Camera CameraNewOrthographic(float size, float depth, float aspectRatio);
Camera CameraNewPerspective(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar);