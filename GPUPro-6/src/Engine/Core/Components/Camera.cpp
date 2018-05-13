#include "stdafx.h"

#include "Engine/Core/Components/Camera.h"
#include "Engine/Core/Graphics/GraphicsSystem.h"

void Camera::SetOrthographic(float size, float depth, float aspectRatio)
{
	Matrix4x4 result;
	Matrix4x4::Identity(result);

	result.M11 = 2 / size;
	result.M22 = aspectRatio * 2 / size;
	result.M33 = 2 / (2 * depth);

	// For lower-left Camera Anchor:
	//result.M41 = -1;
	//result.M42 = -1;

	m_projectionMatrix = result;
}

void Camera::SetPerspective(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar)
{
	Matrix4x4 result;
	Matrix4x4::Identity(result);

	float t = tan(fieldOfViewRadians / 2) * screenNear;
	float b = -t;
	float r = t * aspectRatio;
	float l = -t * aspectRatio;

	result.M11 = (2 * screenNear) / (r - l);
	result.M22 = (2 * screenNear) / (t - b);
	result.M31 = -(l + r) / (r - l);
	result.M32 = -(b + t) / (t - b);
	result.M33 = (screenFar + screenNear) / (screenFar - screenNear);
	result.M34 = 1;
	result.M43 = -(2 * screenFar * screenNear) / (screenFar - screenNear);
	result.M44 = 0;

	m_projectionMatrix = result;
}
