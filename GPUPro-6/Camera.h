#pragma once

#include "Matrix.h"

class Camera
{
public:
	Camera();
	~Camera();
	void Initialize(HWND hwnd, int screenWidth, int screenHeight);
	const Matrix4x4 GetView();
	const Matrix4x4 GetProjection();

private:
	Matrix4x4 m_viewMatrix;
	Matrix4x4 m_projectionMatrix;
};

