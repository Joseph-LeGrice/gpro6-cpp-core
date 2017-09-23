#pragma once

#include "Matrix4x4.h"
#include "Component.h"

class Camera : 
	public Component
{
	friend Entity;

public:
	Camera();
	virtual ~Camera();
	const Matrix4x4 GetView(Entity&);
	const Matrix4x4 GetProjection();

protected:

private:
	Matrix4x4 m_projectionMatrix;

	Matrix4x4 OrthoProject(float size, float depth, float aspectRatio);
	Matrix4x4 PerspProject(float fieldOfView, float aspectRatio, float screenNear, float screenDepth);

	virtual void Init() override;

};

