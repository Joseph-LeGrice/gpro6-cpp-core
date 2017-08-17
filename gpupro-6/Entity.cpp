#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
	m_transform = new Transform();
	m_components = new std::vector<Component*>();
}


Entity::~Entity()
{
	SAFE_DELETE(m_transform);
	for each (Component* c in *m_components)
	{
		SAFE_DELETE(c);
	}
	SAFE_DELETE(m_components);
}

const Transform* Entity::GetTransform()
{
	return m_transform;
}

void Entity::AddComponent(Component* c)
{
	m_components->push_back(c);
}
