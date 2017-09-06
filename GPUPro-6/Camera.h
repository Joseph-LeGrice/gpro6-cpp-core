#pragma once

#include "Matrix4x4.h"
#include "Component.h"

class Camera : 
	public Component
{
	friend Entity;

public:
	const Matrix4x4 GetView();
	const Matrix4x4 GetProjection();

protected:
	Camera();
	virtual ~Camera();

private:
	Matrix4x4 m_projectionMatrix;

	Matrix4x4 OrthoProject(float size, float depth, float aspectRatio);
	Matrix4x4 PerspProjectGL(float fieldOfView, float aspectRatio, float screenNear, float screenDepth);

	virtual void Init() override;

};

