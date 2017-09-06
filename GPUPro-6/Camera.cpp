#include "stdafx.h"
#include "Camera.h"

#include <math.h>
#include "Entity.h"
#include "GameSystem.h"
#include "GraphicsSystem.h"
#include "SceneManagementSystem.h"
#include "SceneGraph.h"
#include "D3DX10.h"

Camera::Camera()
{
	Matrix4x4::MatrixIdentity(&m_projectionMatrix);
}

const Matrix4x4 Camera::GetView()
{
	return GetEntity().GetTranslation();
}

const Matrix4x4 Camera::GetProjection()
{
	return m_projectionMatrix;
}

Matrix4x4 Camera::OrthoProject(float size, float depth, float aspectRatio)
{
	float halfSize = 0.5f * size;

	Matrix4x4 result;
	Matrix4x4::MatrixIdentity(&result);

	result.M11 = 2 / size;
	result.M22 = aspectRatio * 2 / size;
	result.M33 = 2 / (2 * depth);

	// For lower-left Camera Anchor:
	//result.M41 = -1;
	//result.M42 = -1;

	return result;
}

Matrix4x4 Camera::PerspProjectGL(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar)
{
	Matrix4x4 result;
	Matrix4x4::MatrixIdentity(&result);

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

	return result;
}

Matrix4x4 Camera::PerspProjectDX(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar)
{
	Matrix4x4 result;
	Matrix4x4::MatrixIdentity(&result);

	result.M11 = atan(fieldOfViewRadians / 2);
	result.M22 = atan((fieldOfViewRadians * aspectRatio) / 2);
	result.M33 = -(screenFar + screenNear) / (screenFar - screenNear);
	result.M34 = -1;
	result.M43 = -(2 * screenNear * screenFar) / (screenFar - screenNear);
	result.M44 = 0;

	return result;
}

void Camera::Init()
{
	float viewportWidth = GameSystem::Graphics()->GetViewportWidth();
	float viewportHeight = GameSystem::Graphics()->GetViewportHeight();

	float screenNear = 0.1f;
	float screenDepth = 100.0f;
	float fieldOfView = (float)D3DX_PI / 2.0f;

	float aspectRatio = viewportWidth / viewportHeight;
	//m_projectionMatrix = PerspProjectDX(fieldOfView, aspectRatio, screenNear, screenDepth);
	m_projectionMatrix = OrthoProject(0.1f, 50.0f, aspectRatio);

	GameSystem::SceneManager()->GetSceneGraph()->RegisterCamera(*this);
}

Camera::~Camera()
{
}
