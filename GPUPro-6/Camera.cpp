#include "stdafx.h"
#include "Camera.h"
#include "D3DX10.h"
#include <math.h>

Camera::Camera()
{
	Matrix4x4::MatrixIdentity(&m_projectionMatrix);
	Matrix4x4::MatrixIdentity(&m_viewMatrix);
}

void Camera::Initialize(HWND hwnd, float viewportWidth, float viewportHeight)
{
	float screenNear = 0.1f;
	float screenDepth = 100.0f;
	float fieldOfView = (float)D3DX_PI / 2.0f;

	float aspectRatio = viewportWidth / viewportHeight;
	m_projectionMatrix = PerspProject(fieldOfView, aspectRatio, screenNear, screenDepth);
	//m_projectionMatrix = OrthoProject(5.0f, 50.0f, aspectRatio);
}

const Matrix4x4 Camera::GetView()
{
	return m_viewMatrix;
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

Matrix4x4 Camera::PerspProject(float fieldOfViewRadians, float aspectRatio, float screenNear, float screenFar)
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

Camera::~Camera()
{
}
