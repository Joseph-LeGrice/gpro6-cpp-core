#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

void Camera::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	float screenNear = 0.1f;
	float screenDepth = 100.0f;
	float fieldOfView = (float)D3DX_PI / 4.0f;
	float aspectRatio = screenWidth / screenHeight;
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, aspectRatio, screenNear, screenDepth);

	D3DXVECTOR3 eye = D3DXVECTOR3({ 0.0f, 0.0f, -50.0f });
	D3DXVECTOR3 lookAt = D3DXVECTOR3({ 0.0f, 0.0f, 0.0f });
	D3DXVECTOR3 up = D3DXVECTOR3({ 0.0f, 1.0f, 0.0f });
	D3DXMatrixLookAtLH(&m_viewMatrix, &eye, &lookAt, &up);


	//D3DXMatrixIdentity(&m_projectionMatrix);
	//D3DXMatrixIdentity(&m_viewMatrix);
}

const D3DXMATRIX Camera::GetView()
{
	return m_viewMatrix;
}

const D3DXMATRIX Camera::GetProjection()
{
	return m_projectionMatrix;
}

Camera::~Camera()
{
}
