#pragma once

#include "D3DX11.h"
#include "D3DX10.h"

class Camera
{
public:
	Camera();
	~Camera();
	void Initialize(HWND hwnd, int screenWidth, int screenHeight);
	const D3DXMATRIX GetView();
	const D3DXMATRIX GetProjection();

private:
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_projectionMatrix;
};

