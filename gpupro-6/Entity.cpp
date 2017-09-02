#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
	Matrix4x4::MatrixIdentity(&m_translation);
	Matrix4x4::MatrixIdentity(&m_scale);
	Matrix4x4::MatrixIdentity(&m_rotation);
	m_components = new std::vector<Component*>();
}


Entity::~Entity()
{
	m_components->clear();
	SAFE_DELETE(m_components);
}


void Entity::AddComponent(Component* c)
{
	m_components->push_back(c);
}


const std::vector<Component*>* Entity::GetAllComponents()
{
	return m_components;
}

void Entity::SetTranslation(Vector3 position)
{
	m_translation.M41 = position.X;
	m_translation.M42 = position.Y;
	m_translation.M43 = position.Z;
}


void Entity::SetScale(Vector3 scale)
{
	m_scale.M11 = scale.X;
	m_scale.M22 = scale.Y;
	m_scale.M33 = scale.Z;
}


const Matrix4x4 Entity::GetTransformationMatrix()
{
	return m_translation * m_scale * m_rotation;
}
