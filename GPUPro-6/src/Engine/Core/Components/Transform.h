#pragma once

#include "Engine/Core/SceneGraph/IComponent.h"
#include "MyMath/Vector/Vector3.h"
#include "MyMath/Complex/Quaternion.h"

struct Matrix4x4;

struct Transform : IComponent
{
REGISTER_TYPE(Transform);

	// TODO: Child / Parent functionality
	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;

	void SetPosition(Vector3 pos);
	void SetScale(Vector3 scale);
	void SetRotation(Quaternion rotation);

	Vector3 WorldUp();
	Vector3 WorldRight();
	Vector3 WorldForward();

	Matrix4x4 GetMatrix();
	Matrix4x4 GetCameraViewMatrix();
	
	Transform() : IComponent()
	{
		m_scale = { 1.0f, 1.0f, 1.0f };
		m_position = { 0.0f, 0.0f, 0.0f };
		m_rotation = Quaternion::Identity();
	}

	static ComponentTypeID GetComponentType() {
		return 1;
	}
};
