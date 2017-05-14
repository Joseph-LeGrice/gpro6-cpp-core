#pragma once
#include "Vector3.h"
#include "Matrix.h"

class Transform
{
public:
	Transform();
	~Transform();

	void SetTranslation(Vector3 position);
	//void SetRotation(Quaternion rot); //TODO: Quaternions
	void SetScale(Vector3 scale);

	const Matrix4x4 GetTransformationMatrix();

private:
	Matrix4x4 m_scale;
	Matrix4x4 m_rotation;
	Matrix4x4 m_translation;
};

