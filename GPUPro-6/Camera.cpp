#include "stdafx.h"
#include "Camera.h"
#include "D3DX10.h"

Camera::Camera()
{
	Matrix4x4::MatrixIdentity(&m_projectionMatrix);
	Matrix4x4::MatrixIdentity(&m_viewMatrix);
}

void Camera::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	m_projectionMatrix = OrthoProject(25.0f);

	//float screenNear = 0.1f;
	//float screenDepth = 100.0f;
	//float fieldOfView = (float)D3DX_PI / 4.0f;
	//float aspectRatio = screenWidth / screenHeight;
	//m_projectionMatrix = PerspProject(fieldOfView, aspectRatio, screenNear, screenDepth);

	//D3DXVECTOR3 eye = D3DXVECTOR3({ 0.0f, 0.0f, -50.0f });
	//D3DXVECTOR3 lookAt = D3DXVECTOR3({ 0.0f, 0.0f, 0.0f });
	//D3DXVECTOR3 up = D3DXVECTOR3({ 0.0f, 1.0f, 0.0f });
	//D3DXMatrixLookAtLH(&m_viewMatrix, &eye, &lookAt, &up);
}

const Matrix4x4 Camera::GetView()
{
	return m_viewMatrix;
}

const Matrix4x4 Camera::GetProjection()
{
	return m_projectionMatrix;
}

Matrix4x4 Camera::OrthoProject(float size)
{
	Matrix4x4 result;
	Matrix4x4::MatrixIdentity(&result);

	result.M11 = 2 / size;
	result.M22 = 2 / size;
	result.M33 = 2 / size;

	return result;
}

Matrix4x4 Camera::PerspProject(float fieldOfView, float aspectRatio, float screenNear, float screenDepth)
{
	Matrix4x4 result;
	return result;
}

Camera::~Camera()
{
}
