#pragma once

#include <vector>
#include "Matrix.h"
#include "Vector3.h"
#include "Component.h"

class Entity
{
public:
	Entity();
	~Entity();

	void AddComponent(Component* c);
	const std::vector<Component*>* GetAllComponents();

	void SetTranslation(Vector3 position);
	//void SetRotation(Quaternion rot); //TODO: Quaternions
	void SetScale(Vector3 scale);
	// TODO: Add Child / Parent

	const Matrix4x4 GetTransformationMatrix();

private:
	Matrix4x4 m_scale;
	Matrix4x4 m_rotation;
	Matrix4x4 m_translation;

	std::vector<Component*>* m_components;
};

