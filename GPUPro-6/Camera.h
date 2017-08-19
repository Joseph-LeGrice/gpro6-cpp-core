#pragma once

#include "Matrix.h"

class Camera
{
public:
	Camera();
	~Camera();
	void Initialize(float viewportWidth, float viewportHeight);
	const Matrix4x4 GetView();
	const Matrix4x4 GetProjection();

private:
	Matrix4x4 m_viewMatrix;
	Matrix4x4 m_projectionMatrix;

	Matrix4x4 OrthoProject(float size, float depth, float aspectRatio);
	Matrix4x4 PerspProject(float fieldOfView, float aspectRatio, float screenNear, float screenDepth);
};

