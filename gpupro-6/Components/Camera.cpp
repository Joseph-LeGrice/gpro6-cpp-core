#include "stdafx.h"

#include "Components/Camera.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/GraphicsSystem.h"

Camera CameraTestNew()
{
	float viewportWidth = SystemManager::GetSystem<GraphicsSystem>()->GetViewportWidth();
	float viewportHeight = SystemManager::GetSystem<GraphicsSystem>()->GetViewportHeight();
	float aspectRatio = viewportWidth / viewportHeight;

	bool isOrtho = false;
	if (isOrtho)
	{
		return CameraNewOrthographic(0.1f, 50.0f, aspectRatio);
	}
	else
	{
		float screenNear = 0.1f;
		float screenDepth = 100.0f;
		float fieldOfView = (float)D3DX_PI / 2.0f;

		return CameraNewPerspective(fieldOfView, aspectRatio, screenNear, screenDepth);
	}
}

Camera CameraNewOrthographic(float size, float depth, float aspectRatio)
{
	Matrix4x4 result;
	MatrixIdentity(result);

	result.M11 = 2 / size;
	result.M22 = aspectRatio * 2 / size;
	result.M33 = 2 / (2 * depth);

	// For lower-left Camera Anchor:
	//result.M41 = -1;
	//result.M42 = -1;

	Camera c;
	c.m_projectionMatrix = result;
	return c;
}

Camera CameraNewPerspective(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar)
{
	Matrix4x4 result;
	MatrixIdentity(result);

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

	Camera c;
	c.m_projectionMatrix = result;
	return c;
}
